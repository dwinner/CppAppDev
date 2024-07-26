cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellAssign)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellAssign main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp)
