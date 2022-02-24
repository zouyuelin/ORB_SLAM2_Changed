#include <ros/ros.h>  
#include <image_transport/image_transport.h>  
#include <opencv2/highgui/highgui.hpp>  
#include <cv_bridge/cv_bridge.h>  
#include <iostream>
#include <sstream> // for converting the command line parameter to integer  
#include <rs.hpp>

int main(int argc, char** argv)  
{  
    // Check if video source has been passed as a parameter  
    ros::init(argc, argv, "camera_RGBD");  
    ros::NodeHandle nh;  
    image_transport::ImageTransport it(nh);  
    image_transport::Publisher pub_RGB = it.advertise("camera/rgb/image_raw", 1); //camera/rgb/image_raw
    image_transport::Publisher pub_depth = it.advertise("camera/depth_registered/image_raw", 1); 

    rs2::log_to_console(RS2_LOG_SEVERITY_ERROR);

    rs2::config cfg;
    ///设置从设备管道获取的深度图和彩色图的配置对象
    ///配置彩色图像流：分辨率640*480，图像格式：BGR， 帧率：30帧/秒
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
    ///配置深度图像流：分辨率640*480，图像格式：Z16， 帧率：30帧/秒
    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);

    ///生成Realsense管道，用来封装实际的相机设备
    rs2::pipeline pipe;
    ///根据给定的配置启动相机管道
    pipe.start(cfg);

    rs2::frameset data;

    cv::Mat frame;  
    sensor_msgs::ImagePtr rgb_msg; 
    sensor_msgs::ImagePtr depth_msg; 

    ros::Rate loop_rate(5);  
    while (nh.ok()) 
    {  
        data = pipe.wait_for_frames();
        rs2::frame depth  = data.get_depth_frame(); ///获取深度图像数据
        rs2::frame color = data.get_color_frame();  ///获取彩色图像数据
        if (!color || !depth)
        {
            std::cout<<"dfasdfafadf"<<std::endl; 
            break;
        }

        cv::Mat image(cv::Size(640, 480), CV_8UC3, (void*)color.get_data(), cv::Mat::AUTO_STEP);
        cv::Mat depthmat(cv::Size(640, 480), CV_16U, (void*)depth.get_data(), cv::Mat::AUTO_STEP);

            cv::Mat rgb;
            cvtColor(image,rgb,cv::COLOR_BGR2RGB);
            rgb_msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", rgb).toImageMsg(); 
            depth_msg = cv_bridge::CvImage(std_msgs::Header(), "mono16", depthmat).toImageMsg(); 

            pub_RGB.publish(rgb_msg); 
            pub_depth.publish(depth_msg); 
            cv::imshow("/camera/rgb/image_raw",image);
            cv::waitKey(1);  
            //cv::Wait(1); 
    }
    
    ros::spinOnce();  
    loop_rate.sleep();  
}  
