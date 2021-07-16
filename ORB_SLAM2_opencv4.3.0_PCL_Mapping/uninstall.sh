cd build
make clean
cd ..
rm -rf build

cd Thirdparty/DBoW2/build/
make clean
cd ..
rm -rf build

cd ../../
cd Examples/ROS/ORB_SLAM2/build/
make clean
cd ..
rm -rf build
cd ../../../