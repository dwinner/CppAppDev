cmake_minimum_required(VERSION 3.10)
project(PredefinedIdentifiers C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(PredefinedIdentifiers
        main.c)
