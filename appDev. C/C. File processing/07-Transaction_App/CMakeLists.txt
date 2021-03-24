cmake_minimum_required(VERSION 3.8)
project(7_Transaction_App)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c transaction.h transaction.c)
add_executable(7_Transaction_App ${SOURCE_FILES})