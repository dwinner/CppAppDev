cmake_minimum_required(VERSION 3.16)
project(h264_importConsumer C)

set(CMAKE_C_STANDARD 99)

add_executable(h264_importConsumer main.c test_noloop.h264_bin.h payloadUnit.h)