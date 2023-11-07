cmake_minimum_required(VERSION 3.16)
project(web_get C)

set(CMAKE_C_STANDARD 11)

add_executable(web_get main.c network.h web_get.c web_get.h)