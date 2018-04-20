cmake_minimum_required(VERSION 3.10)
project(ListNodeSample C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ListNodeSample
        ListNodeInterface.c
        ListNodeInterface.h
        main.c)
