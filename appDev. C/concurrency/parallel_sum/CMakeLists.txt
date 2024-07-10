cmake_minimum_required(VERSION 3.16)
project(parallel_sum C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(parallel_sum
        main.c
        parallel_sum.c
        parallel_sum.h)
