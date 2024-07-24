cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellExplicitObjectParameter)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellExplicitObjectParameter main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.h)
