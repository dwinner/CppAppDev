cmake_minimum_required(VERSION 3.29)
project(cmpPersonExplicit)

set(CMAKE_CXX_STANDARD 23)

add_executable(cmpPersonExplicit main.cpp
        Person.cpp
        Person.hpp)
