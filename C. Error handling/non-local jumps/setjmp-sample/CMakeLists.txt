cmake_minimum_required(VERSION 3.16)
project(setjmp_sample C)

set(CMAKE_C_STANDARD 11)

add_executable(setjmp_sample main.c calculate.c)