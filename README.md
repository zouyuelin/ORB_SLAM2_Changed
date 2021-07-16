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
source ～/catkin_ws/devel/setup.bash
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
