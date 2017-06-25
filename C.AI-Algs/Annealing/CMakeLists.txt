cmake_minimum_required(VERSION 3.3)
project(Annealing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    commonTypes.h
    entryPoint.c
    helpers.c
    helpers.h)

add_executable(Annealing ${SOURCE_FILES})