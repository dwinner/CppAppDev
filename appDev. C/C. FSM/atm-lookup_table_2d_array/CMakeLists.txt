cmake_minimum_required(VERSION 3.12)
project(atm_lookup_table_2d_array C)

set(CMAKE_C_STANDARD 11)

add_executable(atm_lookup_table_2d_array main.c atm_sm_lookup.c atm_sm_lookup.h)