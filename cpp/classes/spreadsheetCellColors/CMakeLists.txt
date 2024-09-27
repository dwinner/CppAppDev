cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellColors)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellColors main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp)
