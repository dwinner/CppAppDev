cmake_minimum_required(VERSION 3.10)
project(queue_sample)

set(CMAKE_CXX_STANDARD 14)

add_executable(queue_sample main.cpp Customer.cpp Customer.h Queue.cpp Queue.h)