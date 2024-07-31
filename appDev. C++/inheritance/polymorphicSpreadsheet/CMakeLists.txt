cmake_minimum_required(VERSION 3.28)
project(polymorphicSpreadsheet)

set(CMAKE_CXX_STANDARD 23)

add_executable(polymorphicSpreadsheet main.cpp
        SpreadsheetCell.hpp
        DoubleSpreadsheetCell.hpp
        StringSpreadsheetCell.hpp)
