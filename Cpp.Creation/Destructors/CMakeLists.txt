cmake_minimum_required(VERSION 3.6)
project(Destructors)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SpreadsheetCell.h SpreadsheetCell.cpp)
add_executable(Destructors ${SOURCE_FILES} SpreadsheetCell.h SpreadsheetCell.cpp)