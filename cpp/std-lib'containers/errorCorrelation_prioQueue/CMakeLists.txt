cmake_minimum_required(VERSION 3.29)
project(errorCorrelation)

set(CMAKE_CXX_STANDARD 23)

add_executable(errorCorrelation main.cpp
        Error.hpp
        ErrorCorrelator.hpp)
