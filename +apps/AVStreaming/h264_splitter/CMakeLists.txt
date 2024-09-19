cmake_minimum_required(VERSION 3.10)
project(h264_splitter)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(h264_splitter h264Splitter.c)
