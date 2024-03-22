cmake_minimum_required(VERSION 3.27)
project(tspAnt C)

set(CMAKE_C_STANDARD 23)

add_executable(tspAnt main.c
        common.h
        antImpl.c
        antImpl.h)
