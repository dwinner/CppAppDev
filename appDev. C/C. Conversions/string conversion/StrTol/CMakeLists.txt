cmake_minimum_required(VERSION 3.16)
project(StrTol C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(StrTol
        strtol_entry.c)
