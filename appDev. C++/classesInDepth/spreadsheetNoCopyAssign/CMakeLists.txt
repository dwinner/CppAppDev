cmake_minimum_required(VERSION 3.28)
project(spreadsheetNoCopyAssign)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetNoCopyAssign main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp
        Spreadsheet.cpp
        Spreadsheet.hpp)
