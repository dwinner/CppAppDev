cmake_minimum_required(VERSION 3.12)
project(atm_struct_array C)

set(CMAKE_C_STANDARD 11)

add_executable(atm_struct_array main.c atm_struct_sm.c atm_struct_sm.h)