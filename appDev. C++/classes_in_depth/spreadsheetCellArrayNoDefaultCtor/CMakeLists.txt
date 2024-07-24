cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellArrayNoDefaultCtor)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellArrayNoDefaultCtor main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.h)
