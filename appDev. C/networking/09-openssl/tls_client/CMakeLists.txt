cmake_minimum_required(VERSION 3.14)
project(tls_client C)

set(CMAKE_C_STANDARD 11)

add_executable(tls_client main.c ssl_network.h)

target_link_libraries(tls_client ssl crypto)