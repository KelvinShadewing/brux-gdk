git submodule update --init --recursive
mkdir build
cd build
cmake ..
if make; then
	./brux
fi
