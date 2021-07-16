/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/


#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>

#include<opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/cudawarping.hpp>
#include<System.h>

using namespace std;

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        cerr << endl << "Usage: ./mono_tum path_to_vocabulary path_to_settings" << endl;
        return 1;
    }

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::MONOCULAR,true);

    cout << endl << "-------" << endl;
    cout << "Start processing sequence ..." << endl;
    cout << "Images in the sequence: " << endl;

    // Main loop
    cv::Mat im;
    cv::VideoCapture capture(0);

    capture.set(cv::CAP_PROP_FRAME_WIDTH,1920);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT,1080);

    int width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);

    std::cout << "the width is :" << width << std::endl << "the height is :" << height <<std::endl;

    double tframe = 0.0;

    if(!capture.isOpened())
    {
        std::cout<<"can not open the camera with device 0"<<std::endl;
        return -1;
    }
    else
    {
        std::cout<<"open the camera device 0"<<std::endl;
    }

    while(capture.isOpened())
    {
        // Read image from file
        capture >> im;

        if(im.empty())
        {
            capture.release();
            break;
        }
        //cv::Rect rect(width/2-355,height/2-355,750,750);
        //im = im(rect);

        //resize the image
        //cv::cuda::GpuMat Mat1(im);
        //cv::cuda::GpuMat gpuFrame;
        //cv::cuda::resize(Mat1,gpuFrame,cv::Size(600,600));
        //gpuFrame.download(im);

        //Guassblur
        cv::GaussianBlur(im, im, cv::Size(3, 3), 0, 0);

        //medianbulr
        //cv::medianBlur(im, im, 5);

#ifdef COMPILEDWITHC11
        std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
#else
        std::chrono::monotonic_clock::time_point t1 = std::chrono::monotonic_clock::now();
#endif

        // Pass the image to the SLAM system
        SLAM.TrackMonocular(im,tframe);

#ifdef COMPILEDWITHC11
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
#else
        std::chrono::monotonic_clock::time_point t2 = std::chrono::monotonic_clock::now();
#endif

        double ttrack= std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1).count();
        //usleep(33);
        tframe += 0.033;
    }

    // Stop all threads
    SLAM.Shutdown();

    // Save camera trajectory
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");

    return 0;
}
