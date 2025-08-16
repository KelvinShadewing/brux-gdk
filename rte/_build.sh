#!/usr/bin/env bash

set -e

git submodule update --init --recursive

if [[ -d build/CMakeFiles ]]; then
	rm -rf build
fi

if [[ ! -d build ]]; then
	meson setup build
fi

meson compile -C build
