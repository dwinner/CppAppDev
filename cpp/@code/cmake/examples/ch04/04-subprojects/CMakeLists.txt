cmake_minimum_required(VERSION 3.26)
project(Rental CXX)

add_executable(Rental main.cpp)

add_subdirectory(cars)
target_link_libraries(Rental PRIVATE cars)
