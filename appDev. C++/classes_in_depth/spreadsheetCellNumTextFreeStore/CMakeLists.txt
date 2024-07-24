cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellNumTextFreeStore)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellNumTextFreeStore main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.h)
