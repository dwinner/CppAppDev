cmake_minimum_required(VERSION 3.14)
project(https_server C)

set(CMAKE_C_STANDARD 11)

add_executable(https_server main.c ssl_network.h ssl_web_srv.c ssl_web_srv.h)

target_link_libraries(https_server ssl crypto)