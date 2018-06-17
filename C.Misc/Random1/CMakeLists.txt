cmake_minimum_required(VERSION 3.10)
project(Random1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Random1 main.c util/s_and_r.h util/s_and_r.c)