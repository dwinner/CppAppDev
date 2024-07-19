cmake_minimum_required(VERSION 3.28)
project(custom_formattible_types)

set(CMAKE_CXX_STANDARD 23)

add_executable(custom_formattible_types main.cpp
        KeyValue.h
        Formatter.h)
