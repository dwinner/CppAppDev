cmake_minimum_required(VERSION 3.16)
project(friend_forward_decl)

set(CMAKE_CXX_STANDARD 14)

add_executable(friend_forward_decl Remote.h Tv.h Tv.cpp main.cpp)