cmake_minimum_required(VERSION 3.29)
project(cmpPersonSpaceship)

set(CMAKE_CXX_STANDARD 23)

add_executable(cmpPersonSpaceship main.cpp
        Person.cpp
        Person.hpp)
