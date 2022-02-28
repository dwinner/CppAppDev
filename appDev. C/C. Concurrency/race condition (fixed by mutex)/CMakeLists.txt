cmake_minimum_required(VERSION 3.16)
project(race_condition__fixed_by_mutex_ C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(race_condition__fixed_by_mutex_
        inc_dec_mutex.c)
