cmake_minimum_required(VERSION 3.10)
project(dyn_memory_alloc)

set(CMAKE_CXX_STANDARD 14)

add_executable(dyn_memory_alloc main.cpp DmaBase.cpp DmaBase.h LacksDma.cpp LacksDma.h HasDma.cpp HasDma.h)