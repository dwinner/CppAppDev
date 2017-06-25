cmake_minimum_required(VERSION 3.3)
project(_09_Escape)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    entryPoint.c)

add_executable(_09_Escape ${SOURCE_FILES})