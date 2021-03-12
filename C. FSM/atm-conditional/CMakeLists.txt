cmake_minimum_required(VERSION 3.12)
project(atm_conditional C)

set(CMAKE_C_STANDARD 11)

add_executable(atm_conditional main.c atm_sm.c atm_sm.h)