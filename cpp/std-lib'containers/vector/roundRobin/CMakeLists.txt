cmake_minimum_required(VERSION 3.29)
project(vector_roundRobin)

set(CMAKE_CXX_STANDARD 23)

add_executable(vector_roundRobin main.cpp
        RoundRobin.hpp
        Process.hpp
        Scheduler.hpp)
