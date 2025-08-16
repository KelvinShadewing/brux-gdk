#!/usr/bin/env bash

set -e

./_build.sh

./build/brux test/test.nut
