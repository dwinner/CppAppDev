cmake_minimum_required(VERSION 3.16)
project(mtx_timedlock_ex C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(mtx_timedlock_ex
        mtx_timedlock_ex.c)
