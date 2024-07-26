cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellStaticMemberFunctions)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellStaticMemberFunctions main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp)
