cmake_minimum_required(VERSION 3.16)
project(move_semantics)

set(CMAKE_CXX_STANDARD 14)

add_executable(move_semantics main.cpp Useless.cpp Useless.h)