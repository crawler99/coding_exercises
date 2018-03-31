#!/bin/sh

BUILD_DIR="build"
mkdir -p ${BUILD_DIR}

cd ${BUILD_DIR}
rm -fr debug
mkdir debug
cd debug

cmake                                  \
  -DCMAKE_BUILD_TYPE=Debug             \
  -DGCC_ROOT=/usr                      \
  -DBUILD_TESTS=ON                     \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON   \
  ../..
