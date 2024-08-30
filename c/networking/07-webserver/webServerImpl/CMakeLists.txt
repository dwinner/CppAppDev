cmake_minimum_required(VERSION 3.16)
project(webServerImpl C)

set(CMAKE_C_STANDARD 11)

add_executable(webServerImpl main.c network.h)