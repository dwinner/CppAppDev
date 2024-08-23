cmake_minimum_required(VERSION 3.29)
project(dereferenceOps)

set(CMAKE_CXX_STANDARD 23)

add_executable(dereferenceOps main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp
        Pointer.hpp)
