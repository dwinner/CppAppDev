cmake_minimum_required(VERSION 3.16)
project(tss_sample C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(tss_sample
        thread_specific_storage.c)
