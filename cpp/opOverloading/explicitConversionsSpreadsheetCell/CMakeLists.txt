cmake_minimum_required(VERSION 3.29)
project(explicitConversionsSpreadsheetCell)

set(CMAKE_CXX_STANDARD 23)

add_executable(explicitConversionsSpreadsheetCell main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.hpp)
