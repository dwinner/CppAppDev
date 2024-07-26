cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellUnnamedNamespace)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellUnnamedNamespace main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp)
