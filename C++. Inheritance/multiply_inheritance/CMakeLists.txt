cmake_minimum_required(VERSION 3.10)
project(multiply_inheritance)

set(CMAKE_CXX_STANDARD 14)

add_executable(multiply_inheritance main.cpp Worker.cpp Worker.h Waiter.cpp Waiter.h Singer.cpp Singer.h SingingWaiter.cpp SingingWaiter.h)