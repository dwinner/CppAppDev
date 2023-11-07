cmake_minimum_required(VERSION 3.16)
project(connect_blocking C)

set(CMAKE_C_STANDARD 11)

add_executable(connect_blocking main.c network.h)