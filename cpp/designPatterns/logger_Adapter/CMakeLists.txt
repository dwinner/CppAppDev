cmake_minimum_required(VERSION 3.29)
project(logger_Adapter)

set(CMAKE_CXX_STANDARD 23)

add_executable(logger_Adapter main.cpp
        Loggers.cpp
        Loggers.hpp)
