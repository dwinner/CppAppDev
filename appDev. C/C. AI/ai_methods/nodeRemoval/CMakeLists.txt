cmake_minimum_required(VERSION 3.25)
project(nodeRemoval C)

set(CMAKE_C_STANDARD 23)

add_executable(nodeRemoval main.c removal.c removal.h)
