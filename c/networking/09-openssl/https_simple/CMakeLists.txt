cmake_minimum_required(VERSION 3.14)
project(https_simple C)

set(CMAKE_C_STANDARD 11)

add_executable(https_simple main.c ssl_network.h)

target_link_libraries(https_simple ssl crypto)