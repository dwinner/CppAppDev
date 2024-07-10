cmake_minimum_required(VERSION 3.27)
project(backPropagation C)

set(CMAKE_C_STANDARD 23)

add_executable(backPropagation main.c
        neuroController.c
        neuroController.h)
