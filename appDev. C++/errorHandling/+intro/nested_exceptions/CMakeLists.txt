cmake_minimum_required(VERSION 3.16)
project(nested_exceptions)

set(CMAKE_CXX_STANDARD 14)

add_executable(nested_exceptions main.cpp Sales.cpp Sales.h LabeledSales.cpp LabeledSales.h)