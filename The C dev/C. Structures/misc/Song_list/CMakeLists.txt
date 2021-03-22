cmake_minimum_required(VERSION 3.17)
project(Song_list C)

set(CMAKE_C_STANDARD 11)

add_executable(Song_list main.c song_list.c song_list.h)