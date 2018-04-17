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
  -DGTEST_ROOT=/usr/local              \
  -DGMOCK_ROOT=/usr/local              \
  -DBUILD_TESTS=ON                     \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON   \
  ../..
