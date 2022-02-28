cmake_minimum_required(VERSION 3.16)
project(tss_set_ex C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(tss_set_ex
        tss_set_ex.c)
