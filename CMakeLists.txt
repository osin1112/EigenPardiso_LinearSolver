cmake_minimum_required(VERSION 3.16)

option(enable_OPENMP "Enable OpenMP" ON)
option(enable_GLOG "Enable GLOG" ON)

#-----compiler options
if(compiler STREQUAL intel)
  set(CMAKE_C_COMPILER "icx")
  set(CMAKE_CXX_COMPILER "icpx")
  set(base_compile_options "-Wall -Wextra -O3 -lm -qopenmp -mkl -DESIGN_USE_MKL_ALL")
elseif(DEFINED compiler)
  message(FATAL ERROR "invalid compiler")
endif()
string(REPLACE " " ";" compile_options ${base_compile_options})
#-----------------------

project(test C CXX)
set(CMAKE_CXX_STANDARD 20)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

#change default install prefix
set(INSTALL_DIR "/usr/local/test")
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${INSTALL_DIR} CACHE PATH "..." FORCE)
endif()

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_MODULE_PATH  ${PROJECT_SOURCE_DIR}/cmake)

#######
# Display options
#######
message(" ")
message("${PROJECT_NAME}")
message( STATUS "Destination PATH      : "      ${CMAKE_INSTALL_PREFIX})
message( STATUS "CMAKE_CXX_COMPILER    : "      ${CMAKE_CXX_COMPILER})
message( STATUS "COMPILE_OPTIONS       : "      ${compile_options})
message(" ")

#######
# find Libraries
#######
# TextParser
set(TP_DIR ${TP_DIR} CACHE PATH "...")
find_package(TP REQUIRED)
include_directories(${TP_INCLUDE_DIR})

# Google-glog
if(enable_GLOG)
  set(GLOG_DIR ${GLOG_DIR} CACHE PATH "...")
  find_package(GLOG REQUIRED)
  include_directories(${GLOG_INCLUDE_DIR})
  message( STATUS "GLOG include dir  : "      ${GLOG_INCLUDE_DIR})
  MESSAGE("find GLOG")
endif()

# Eigen
find_package(Eigen REQUIRED)
include_directories(${EIGEN_INCLUDE_DIR})

# VTK
find_package(VTK REQUIRED)
include_directories(${VTK_INCLUDE_DIRS})

# MKL
set(MKL_ARCH "intel64")
set(MKL_LINK "static")
set(MKL_INTERFACE "lp64")
set(MKL_THREADING "tbb_thread")
set(MKL_MPI "intelmpi")
find_package(MKL REQUIRED C CXX)
include_directories(${MKL_INCLUDE_DIR})
MESSAGE(${MKL_LIBRARIES})

# TBB
find_package(TBB REQUIRED)
include_directories(${TBB_INCLUDE_DIR})

#######
# Sub Directories
#######
add_subdirectory(src)