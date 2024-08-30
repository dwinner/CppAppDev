cmake_minimum_required(VERSION 3.29)
project(arithmeticOperators)

set(CMAKE_CXX_STANDARD 23)

add_executable(arithmeticOperators main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp)
