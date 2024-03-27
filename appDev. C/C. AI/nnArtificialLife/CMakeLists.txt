cmake_minimum_required(VERSION 3.27)
project(nnArtificialLife C)

set(CMAKE_C_STANDARD 23)

add_executable(nnArtificialLife main.c
        common.h
        neuralNetwork.c
        neuralNetwork.h
        common.c)
