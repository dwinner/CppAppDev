cmake_minimum_required(VERSION 3.16)
project(readingH264Frame C)

set(CMAKE_C_STANDARD 11)

add_executable(readingH264Frame main.c h264_read_frame.c h264_read_frame.h)