cmake_minimum_required(VERSION 3.14)
project(select_server C)

set(CMAKE_C_STANDARD 11)

add_executable(select_server main.c network_utils.c network_utils.h)