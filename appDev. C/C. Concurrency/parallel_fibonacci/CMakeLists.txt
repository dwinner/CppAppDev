cmake_minimum_required(VERSION 3.16)
project(parallel_fibonacci C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(parallel_fibonacci
        parallel_fibonacci.c)
