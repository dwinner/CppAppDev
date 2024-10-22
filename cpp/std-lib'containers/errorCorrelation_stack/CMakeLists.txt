cmake_minimum_required(VERSION 3.29)
project(errorCorrelation_stack)

set(CMAKE_CXX_STANDARD 23)

add_executable(errorCorrelation_stack main.cpp
        Error.hpp
        ErrorCorrelator.hpp)
