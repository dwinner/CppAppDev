cmake_minimum_required(VERSION 3.16)
project(call_once C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(call_once
        call_once.c)
