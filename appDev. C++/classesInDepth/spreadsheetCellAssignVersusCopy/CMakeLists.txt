cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellAssignVersusCopy)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellAssignVersusCopy main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp)
