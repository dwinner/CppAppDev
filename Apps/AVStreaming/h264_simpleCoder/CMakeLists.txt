cmake_minimum_required(VERSION 3.16)
project(h264simpleCoder)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(h264simpleCoder
        CJOCh264bitstream.cpp
        CJOCh264bitstream.h
        CJOCh264encoder.cpp
        CJOCh264encoder.h
        h264simpleCoder.cpp
        makefile
        README.md)
