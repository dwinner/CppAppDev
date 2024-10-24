cmake_minimum_required(VERSION 3.29)
project(processorCallbacks)

set(CMAKE_CXX_STANDARD 23)

add_executable(processorCallbacks main.cpp
        Processor.cpp
        Processor.hpp)
