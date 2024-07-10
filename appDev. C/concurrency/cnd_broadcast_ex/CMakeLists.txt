cmake_minimum_required(VERSION 3.16)
project(cnd_broadcast_ex C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(cnd_broadcast_ex
        cnd_broadcast_ex.c)
