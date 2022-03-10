cmake_minimum_required(VERSION 3.16)
project(h264_splitByFrames C)

set(CMAKE_C_STANDARD 11)

add_executable(h264_splitByFrames main.c h264_stream.c h264_stream.h bs.h h264_sei.c h264_sei.h h264_nal.c h264_nal.h)