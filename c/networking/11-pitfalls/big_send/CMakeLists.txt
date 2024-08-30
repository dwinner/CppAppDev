cmake_minimum_required(VERSION 3.16)
project(big_send C)

set(CMAKE_C_STANDARD 11)

add_executable(big_send main.c network.h)