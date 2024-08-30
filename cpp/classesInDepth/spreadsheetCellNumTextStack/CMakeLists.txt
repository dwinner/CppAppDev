cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellNumTextStack)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellNumTextStack main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.h)
