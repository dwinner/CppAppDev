cmake_minimum_required(VERSION 3.16)
project(h264bitstream C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(h264bitstream
        bs.h
        h264_analyze.c
        h264_avcc.c
        h264_avcc.h
        h264_sei.c
        h264_sei.h
        h264_stream.c
        h264_stream.h)
