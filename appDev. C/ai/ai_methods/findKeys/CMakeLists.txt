cmake_minimum_required(VERSION 3.27)
project(findKeys C)

set(CMAKE_C_STANDARD 23)

add_executable(findKeys main.c
        finder.c
        finder.h)
