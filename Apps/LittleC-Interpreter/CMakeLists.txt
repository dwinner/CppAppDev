cmake_minimum_required(VERSION 3.10)
project(LittleC_Interpreter C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(LittleC_Interpreter
        lclib.c
        lclib.h
        main.c parser.c parser.h)
