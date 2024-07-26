cmake_minimum_required(VERSION 3.28)
project(spreadsheetMoveSemantics)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetMoveSemantics main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp
        Spreadsheet.cpp
        Spreadsheet.hpp)
