cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellNumTextFreeStoreAlternate)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellNumTextFreeStoreAlternate main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.h)
