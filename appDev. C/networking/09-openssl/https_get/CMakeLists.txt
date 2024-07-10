cmake_minimum_required(VERSION 3.14)
project(https_get C)

set(CMAKE_C_STANDARD 11)

add_executable(https_get main.c ssl_network.h ssl_web_get.c ssl_web_get.h)

target_link_libraries(https_get ssl crypto)