# 发布话题供ORB_SLAM2 使用, 专用realsense相机

```shell
"camera/rgb/image_raw"
"camera/depth_registered/image_raw" 
```

# 构建方法
复制到 ~/catkin_ws/src/
cd ~/catkin_ws
cakin_make

# 运行
```shell
source ~/catkin_ws/devel/setup.bash
rosrun RGBD_camera camera_RGBD_node
```
