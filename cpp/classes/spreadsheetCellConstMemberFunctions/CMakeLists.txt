cmake_minimum_required(VERSION 3.28)
project(spreadsheetCellConstMemberFunctions)

set(CMAKE_CXX_STANDARD 23)

add_executable(spreadsheetCellConstMemberFunctions main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp)
