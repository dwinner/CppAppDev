cmake_minimum_required(VERSION 3.16)
project(producer_consumer C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(producer_consumer
        circular_buffer.c
        circular_buffer.h
        main.c)
