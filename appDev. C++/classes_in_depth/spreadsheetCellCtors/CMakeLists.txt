cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellCtors)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellCtors main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.h)
