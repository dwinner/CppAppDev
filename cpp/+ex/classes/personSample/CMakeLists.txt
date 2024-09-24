cmake_minimum_required(VERSION 3.29)
project(personSample)

set(CMAKE_CXX_STANDARD 23)

add_executable(personSample main.cpp
        Person.cpp
        Person.hpp)
