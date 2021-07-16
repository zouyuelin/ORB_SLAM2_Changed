相关源码原本是高翔针对PCL建图修改得到的，但库和软件更新很快，安装新版的opencv，pcl等库甚至是新版的ubuntu操作系统都无法正常运行。
本人就这些问题在高翔 ORB_SLAM2_PCL_Mapping源码上进行了部分修改，可以正常在Ubuntu 20.04,OpenCV 4.2.0 ，Eigen3.5以上的环境中运行。


# 建立ROS文件夹 
```shell
mkdir -P ~/catkin_ws/src
cd ..
catkin_make
```


# 把下载的文件ORB_SLAM2_opencv4.3.0_PCL_Mapping放到~/catkin_ws/src文件中
# 文件夹 g2o_with_orbslam2 随意放置，默认放在一起，但另一个文件夹一定要在ROS的工作空间里

# 针对ros的路径设置我们需要在~/.bashrc文件中加入下面两行
```shell
source /opt/ros/noetic/setup.bash
source ~/catkin_ws/devel/setup.bash
```

# 然后执行
```shell
source ~/.bashrc
```

# 需要下载usb_cam才能使用
```shell
cd ~/catkin_ws/src
git clone https://github.com/bosch-ros-pkg/usb_cam.git usb_cam
cd ~/catkin_ws
catkin_make
```


# 首先到<font color=red>g2o_with_orbslam2</font>文件夹 编译g2o
```shell
mkdir build
cd build 
cmake ..
make -j4
sudo make install
```


# 安装完后，到文件夹 ORB_SLAM2_opencv4.3.0_PCL_Mapping/ 中执行
```shell
source ./build.sh
source ./build_ros.h
```

# 如遇到错误自行百度解决

# 运行方法
```shell
roscore 
roslaunch usb_cam usb_cam-test.launch
rosrun ORB_SLAM2 Mono ./Vocabulary/ORBvoc.txt Examples/ROS/ORB_SLAM2/Asus.yaml
```

# 如果要卸载
```shell
source uninstall.sh
```
