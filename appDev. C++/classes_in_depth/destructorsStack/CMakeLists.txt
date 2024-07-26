cmake_minimum_required(VERSION 3.28)
project(destructorsStack)

set(CMAKE_CXX_STANDARD 23)

add_executable(destructorsStack main.cpp
        SpreadsheetCell.cpp
        SpreadsheetCell.h)
