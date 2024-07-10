cmake_minimum_required(VERSION 3.17)
project(SetNewName C)

set(CMAKE_C_STANDARD 11)

add_executable(SetNewName main.c set_new_name.c set_new_name.h)