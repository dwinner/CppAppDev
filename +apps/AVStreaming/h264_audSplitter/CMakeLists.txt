cmake_minimum_required(VERSION 3.16)
project(h264_audSplitter)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(h264_audSplitter
        H264FileReader.cpp
        H264FileReader.h
        main.cpp
        Nalu.h)
