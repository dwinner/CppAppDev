cmake_minimum_required(VERSION 3.14)
project(tls_get_cert C)

set(CMAKE_C_STANDARD 11)

add_executable(tls_get_cert main.c ssl_network.h)

target_link_libraries(tls_get_cert ssl crypto)