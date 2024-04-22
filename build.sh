#!/bin/sh
rm -r BUILD bin build
mkdir BUILD bin
cd BUILD

INSTALL_DIR=../bin

cmake -D compiler=intel \
      -D enable_GLOG=ON \
      -D CMAKE_INSTALL_PREFIX=$INSTALL_DIR \
      ..
make -j8 && make install