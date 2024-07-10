cmake_minimum_required(VERSION 3.16)
project(server_reuse C)

set(CMAKE_C_STANDARD 11)

add_executable(server_reuse main.c network.h)