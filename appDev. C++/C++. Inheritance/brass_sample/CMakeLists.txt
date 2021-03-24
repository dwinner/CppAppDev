cmake_minimum_required(VERSION 3.10)
project(brass_sample)

set(CMAKE_CXX_STANDARD 14)

add_executable(brass_sample main.cpp AccountBase.cpp AccountBase.h Brass.cpp Brass.h BrassPlus.cpp BrassPlus.h)