cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellCopyCtor)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellCopyCtor main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.h)
