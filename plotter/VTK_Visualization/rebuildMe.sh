rm -rf ./build/debian
mkdir ./build/debian
cd ./build/debian
cmake ../..
make -j4
