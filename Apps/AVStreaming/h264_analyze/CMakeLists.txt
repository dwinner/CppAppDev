cmake_minimum_required(VERSION 3.16)
project(h264_analyze C)

set(CMAKE_C_STANDARD 11)

add_executable(h264_analyze main.c h264_nal.c h264_nal.h h264_sei.c h264_sei.h bs.h h264_stream.c h264_stream.h)