cmake_minimum_required(VERSION 3.16)
project(tcp_client C)

set(CMAKE_C_STANDARD 11)

add_executable(tcp_client ../network.h main.c)