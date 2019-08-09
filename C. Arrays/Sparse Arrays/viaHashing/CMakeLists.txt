cmake_minimum_required(VERSION 3.14)
project(viaHashing C)

set(CMAKE_C_STANDARD 11)

add_executable(viaHashing main.c hash_cell.c hash_cell.h)