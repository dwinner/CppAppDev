cmake_minimum_required(VERSION 3.16)
project(thread_local_ex C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(thread_local_ex
        thread_local.c)
