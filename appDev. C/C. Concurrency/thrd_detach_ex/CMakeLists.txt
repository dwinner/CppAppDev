cmake_minimum_required(VERSION 3.16)
project(thrd_detach_ex C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(thrd_detach_ex
        thrd_detach_ex.c)
