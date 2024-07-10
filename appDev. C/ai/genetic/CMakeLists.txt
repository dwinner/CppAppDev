cmake_minimum_required(VERSION 3.27)
project(genetic C)

set(CMAKE_C_STANDARD 23)

add_executable(genetic main.c
        common.h
        fitness.c
        init.c
        select.c
        stm.c)
