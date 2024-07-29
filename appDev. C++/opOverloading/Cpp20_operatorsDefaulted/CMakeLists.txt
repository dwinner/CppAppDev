cmake_minimum_required(VERSION 3.28)
project(Cpp20_operatorsDefaulted)

set(CMAKE_CXX_STANDARD 23)

add_executable(Cpp20_operatorsDefaulted main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp)
