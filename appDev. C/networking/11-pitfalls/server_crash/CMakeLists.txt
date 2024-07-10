cmake_minimum_required(VERSION 3.16)
project(server_crash C)

set(CMAKE_C_STANDARD 11)

add_executable(server_crash main.c network.h)