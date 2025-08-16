#!/usr/bin/env

set -e

cd rte && ./_build.sh && cd ..;
cd ide && meson setup build && meson compile -C build && cd ..
