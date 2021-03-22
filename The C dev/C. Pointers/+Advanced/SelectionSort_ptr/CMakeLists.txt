cmake_minimum_required(VERSION 3.17)
project(SelectionSort_ptr C)

set(CMAKE_C_STANDARD 11)

add_executable(SelectionSort_ptr main.c selection_sort.c selection_sort.h)