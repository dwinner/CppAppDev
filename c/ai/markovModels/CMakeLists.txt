cmake_minimum_required(VERSION 3.27)
project(markovModels C)

set(CMAKE_C_STANDARD 23)

add_executable(markovModels main.c
        bigram.c
        bigram.h)
