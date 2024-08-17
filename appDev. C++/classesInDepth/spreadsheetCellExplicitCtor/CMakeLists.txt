cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellExplicitCtor)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellExplicitCtor main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.h)
