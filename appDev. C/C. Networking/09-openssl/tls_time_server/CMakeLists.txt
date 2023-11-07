cmake_minimum_required(VERSION 3.14)
project(tls_time_server C)

set(CMAKE_C_STANDARD 11)

add_executable(tls_time_server main.c ssl_network.h)

target_link_libraries(tls_time_server ssl crypto)