git submodule update --init --recursive
mkdir build
cd build
cmake .. -DGENERATE_WRAPPER=ON
cmake --build .
./brux
