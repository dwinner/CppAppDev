cmake_minimum_required(VERSION 3.25)
project(longestDistance C)

set(CMAKE_C_STANDARD 23)

add_executable(longestDistance main.c hillClimbing.c hillClimbing.h)
