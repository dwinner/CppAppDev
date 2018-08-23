cmake_minimum_required(VERSION 3.10)
project(LC_Interpreter C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(LC_Interpreter
        common_defines.h
        lclib.c
        lclib.h
        littlec.c
        littlec.h
        main.c
        parser.c
        parser.h)
