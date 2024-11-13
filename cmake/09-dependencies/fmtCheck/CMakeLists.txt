cmake_minimum_required(VERSION 3.10)

project(fmtCheck)

find_package(fmt CONFIG REQUIRED)

add_executable(fmtCheck fmtCheck.cpp)

target_link_libraries(fmtCheck PRIVATE fmt::fmt)