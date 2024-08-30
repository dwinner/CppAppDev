cmake_minimum_required(VERSION 3.28)
project(Cpp20Operators)

set(CMAKE_CXX_STANDARD 23)

add_executable(Cpp20Operators main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp)
