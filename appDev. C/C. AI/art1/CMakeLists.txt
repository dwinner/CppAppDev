cmake_minimum_required(VERSION 3.27)
project(art1 C)

set(CMAKE_C_STANDARD 23)

add_executable(art1 main.c
        artPers.c
        artPers.h)
