cmake_minimum_required(VERSION 3.29)
project(conversionsPointerBool)

set(CMAKE_CXX_STANDARD 23)

add_executable(conversionsPointerBool main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp
        Pointer.hpp)
