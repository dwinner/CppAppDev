cmake_minimum_required(VERSION 3.29)
project(ptrsToMemberFunctionsAndMembers)

set(CMAKE_CXX_STANDARD 23)

add_executable(ptrsToMemberFunctionsAndMembers main.cpp
        Employee.cpp
        Employee.hpp)
