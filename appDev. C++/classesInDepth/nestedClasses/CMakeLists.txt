cmake_minimum_required(VERSION 3.28)
project(nestedClasses)

set(CMAKE_CXX_STANDARD 23)

add_executable(nestedClasses main.cpp
        Spreadsheet.cpp
        Spreadsheet.hpp)
