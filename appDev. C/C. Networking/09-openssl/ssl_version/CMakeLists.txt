cmake_minimum_required(VERSION 3.14)
project(ssl_version C)

set(CMAKE_C_STANDARD 11)

add_executable(ssl_version main.c)

target_link_libraries(ssl_version ssl crypto)