# 针对ros的路径设置我们需要在~/.bashrc文件中加入下面两行
source /opt/ros/noetic/setup.bash
source ～/catkin_ws/devel/setup.bash
# 然后执行
source ~/.bashrc

# 需要下载usb_cam才能使用
cd ~/catkin_ws/src
git clone https://github.com/bosch-ros-pkg/usb_cam.git usb_cam
cd ~/catkin_ws
catkin_make

# 这里需要单独安装g2o

# 安装完后，执行
source ./build.sh
source ./build_ros.h

# 如遇到错误自行百度解决

# 运行方法
roscore 
roslaunch usb_cam usb_cam-test.launch
rosrun ORB_SLAM2 Mono ./Vocabulary/ORBvoc.txt Examples/ROS/ORB_SLAM2/Asus.yaml

# 如果要卸载
source uninstall.sh
