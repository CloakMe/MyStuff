rm -rf ./build-debug
mkdir ./build-debug
cd ./build-debug
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-g" ..
make -j4
