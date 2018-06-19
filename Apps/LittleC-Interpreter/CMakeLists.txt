cmake_minimum_required(VERSION 3.10)
project(LittleC_Interpreter C)

set(CMAKE_C_STANDARD 11)

add_executable(LittleC_Interpreter main.c lclib.h lclib.c)