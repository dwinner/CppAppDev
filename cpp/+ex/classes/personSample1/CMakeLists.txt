cmake_minimum_required(VERSION 3.29)
project(personSample1)

set(CMAKE_CXX_STANDARD 23)

add_executable(personSample1 main.cpp
        Person.cpp
        Person.hpp)
