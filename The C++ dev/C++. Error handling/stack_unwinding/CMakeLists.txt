cmake_minimum_required(VERSION 3.16)
project(stack_unwinding)

set(CMAKE_CXX_STANDARD 14)

add_executable(stack_unwinding error_classes.h main.cpp)