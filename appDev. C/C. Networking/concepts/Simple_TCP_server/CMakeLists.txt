cmake_minimum_required(VERSION 3.16)
project(Simple_TCP_server)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Simple_TCP_server
        main.cpp)
