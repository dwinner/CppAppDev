cmake_minimum_required(VERSION 3.29)
project(logger_Singleton)

set(CMAKE_CXX_STANDARD 23)

add_executable(logger_Singleton main.cpp
        Logger.cpp
        Logger.hpp)
