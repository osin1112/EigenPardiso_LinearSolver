#!/bin/sh

# buildメッセージは ./BUILD/build.log に吐くようにし，エラーメッセージだけをstdoutに出力．
rm -r BUILD bin
mkdir BUILD bin
cd BUILD

INSTALL_DIR=../bin
cmake -D compiler=intel \
      -D enable_GLOG=ON \
      -D CMAKE_INSTALL_PREFIX=$INSTALL_DIR \
      .. > build.log 2>&1
make -j8 >> build.log 2>&1 && make install >> build.log 2>&1

grep -i error build.log && cat build.log | grep -i error