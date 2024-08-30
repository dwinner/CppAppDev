cmake_minimum_required(VERSION 3.29)
project(operatorAutoSpreadsheetCell)

set(CMAKE_CXX_STANDARD 23)

add_executable(operatorAutoSpreadsheetCell main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp)
