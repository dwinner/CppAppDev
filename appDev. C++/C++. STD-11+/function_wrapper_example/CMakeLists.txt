cmake_minimum_required(VERSION 3.16)
project(function_wrapper_example)

set(CMAKE_CXX_STANDARD 14)

add_executable(function_wrapper_example main.cpp somedefs.h)