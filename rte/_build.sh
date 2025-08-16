#!/usr/bin/env bash

set -e

git submodule update --init --recursive

if [[ -d build/CMakeFiles ]]; then
	rm -rf build
fi

if [[ ! -d build ]]; then
	meson setup build
elif [[ ! -f build/meson-info/meson-info.json ]]; then
	echo Missing meson-info.json, resetting up...
	meson setup build --wipe
fi

meson compile -C build
