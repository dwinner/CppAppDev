cmake_minimum_required(VERSION 3.16)
project(friend_class_sample)

set(CMAKE_CXX_STANDARD 14)

add_executable(friend_class_sample main.cpp Tv.cpp Tv.h Remote.h)