cmake_minimum_required(VERSION 3.16)
project(race_condition C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(race_condition
        race_condition.c)
