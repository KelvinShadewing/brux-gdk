git submodule update --init --recursive

if [[ ! -d build ]]; then
	mkdir build
	cd build
	cmake .. -DGENERATE_WRAPPER=ON
else
	cd build
fi

cmake --build . && ./brux
