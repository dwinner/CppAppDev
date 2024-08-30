cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellNumTextSmartPointer)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellNumTextSmartPointer main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.h)
