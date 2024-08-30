cmake_minimum_required(VERSION 3.29)
project(conversionsPointer)

set(CMAKE_CXX_STANDARD 23)

add_executable(conversionsPointer main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp
        Pointer.hpp)
