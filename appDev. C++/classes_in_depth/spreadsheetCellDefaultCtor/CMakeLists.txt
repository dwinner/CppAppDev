cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellDefaultCtor)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellDefaultCtor main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.h)
