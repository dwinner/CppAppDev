cmake_minimum_required(VERSION 3.29)
project(personSample2)

set(CMAKE_CXX_STANDARD 23)

add_executable(personSample2 main.cpp
        Person.cpp
        Person.hpp)
