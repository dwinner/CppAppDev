cmake_minimum_required(VERSION 3.29)
project(logger_Strategy)

set(CMAKE_CXX_STANDARD 23)

add_executable(logger_Strategy main.cpp
        ILogger.hpp
        Logger.cpp
        Logger.hpp
)
