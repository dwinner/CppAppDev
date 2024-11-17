cmake_minimum_required(VERSION 3.29)
project(cppLib)

set(CMAKE_CXX_STANDARD 23)

add_library(cppLib SHARED library.cpp)
