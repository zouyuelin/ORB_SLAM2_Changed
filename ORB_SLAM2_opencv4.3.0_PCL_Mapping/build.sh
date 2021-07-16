echo "Configuring and building Thirdparty/DBoW2 ..."

cd Vocabulary
tar vxf ORBvoc.tar.gz
cd ..

cd Thirdparty/DBoW2
rm -rf build/
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j8

cd ../../../

echo "Configuring and building ORB_SLAM2 ..."

rm -rf build/
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j8
cd ..
