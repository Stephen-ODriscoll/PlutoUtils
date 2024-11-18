#!/bin/bash

mkdir -p build
cd build
cmake .. -G Xcode -D CMAKE_CXX_STANDARD=20
cd ..
