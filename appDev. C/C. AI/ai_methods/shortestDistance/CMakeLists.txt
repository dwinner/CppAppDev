cmake_minimum_required(VERSION 3.27)
project(shortestDistance C)

set(CMAKE_C_STANDARD 23)

add_executable(shortestDistance main.c
        sd.c
        sd.h)
