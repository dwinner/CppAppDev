cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellDelegatingCtor)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellDelegatingCtor main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.h)
