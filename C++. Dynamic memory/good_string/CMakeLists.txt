cmake_minimum_required(VERSION 3.10)
project(good_string)

set(CMAKE_CXX_STANDARD 14)

add_executable(good_string main.cpp GoodString.cpp GoodString.h)