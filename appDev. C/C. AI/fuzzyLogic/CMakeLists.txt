cmake_minimum_required(VERSION 3.27)
project(fuzzyLogic C)

set(CMAKE_C_STANDARD 23)

add_executable(fuzzyLogic main.c
        fuzzy.c
        fuzzy.h
        mbrship.c
        mbrship.h
        simulate.c
        simulate.h)
