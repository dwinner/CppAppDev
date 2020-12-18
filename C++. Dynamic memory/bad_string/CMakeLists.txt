cmake_minimum_required(VERSION 3.10)
project(bad_string)

set(CMAKE_CXX_STANDARD 14)

add_executable(bad_string main.cpp BadString.cpp BadString.h)