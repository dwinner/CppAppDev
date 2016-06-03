cmake_minimum_required(VERSION 3.3)
project(Creation_C__)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp PointSequence.cpp PointSequence.h)
add_executable(Creation_C__ ${SOURCE_FILES})