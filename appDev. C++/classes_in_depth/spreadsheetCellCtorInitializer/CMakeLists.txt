cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellCtorInitializer)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellCtorInitializer main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.h)
