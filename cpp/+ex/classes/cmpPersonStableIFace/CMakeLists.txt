cmake_minimum_required(VERSION 3.29)
project(cmpPersonStableIFace)

set(CMAKE_CXX_STANDARD 23)

add_executable(cmpPersonStableIFace main.cpp
        Person.cpp
        Person.hpp 
        Person.Impl.cpp
        Person.Impl.hpp
)
