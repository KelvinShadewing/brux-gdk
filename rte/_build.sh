git submodule update --init --recursive
mkdir build
cd build
cmake .. -DGENERATE_WRAPPER=ON
cd ..
cmake --build build
