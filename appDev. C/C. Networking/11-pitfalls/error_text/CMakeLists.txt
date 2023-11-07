cmake_minimum_required(VERSION 3.16)
project(error_text C)

set(CMAKE_C_STANDARD 11)

add_executable(error_text main.c network.h error_handling.c error_handling.h)