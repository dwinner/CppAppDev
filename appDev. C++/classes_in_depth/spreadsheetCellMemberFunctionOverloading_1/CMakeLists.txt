cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellMemberFunctionOverloading_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellMemberFunctionOverloading_1 main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp
        Spreadsheet.cpp
        Spreadsheet.hpp)
