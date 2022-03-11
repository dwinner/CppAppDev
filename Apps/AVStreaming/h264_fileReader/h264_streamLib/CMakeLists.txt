cmake_minimum_required(VERSION 3.16)
project(h264streamLib C)

set(CMAKE_C_STANDARD 11)

add_library(h264streamLib SHARED
            h264_nal.c
            h264_nal.h
            h264_sei.c
            h264_sei.h
            h264_stream.c
            h264_stream.h
            bs.h)