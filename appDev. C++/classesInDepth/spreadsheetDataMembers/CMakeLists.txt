cmake_minimum_required(VERSION 3.28)
project(spreadsheetDataMembers)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetDataMembers main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp
        Spreadsheet.cpp
        Spreadsheet.hpp)
