#!/bin/sh

BUILD_DIR="build"
mkdir -p ${BUILD_DIR}

cd ${BUILD_DIR}
rm -fr release
mkdir release
cd release

cmake                                  \
  -DCMAKE_BUILD_TYPE=Release           \
  -DGCC_ROOT=/usr                      \
  -DBUILD_TESTS=ON                     \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON   \
  ../..
