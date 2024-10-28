cmake_minimum_required(VERSION 3.29)
project(personVariants)

set(CMAKE_CXX_STANDARD 23)

add_executable(personVariants
   main.cpp
   Person.cpp
   Person.hpp
   Employee.cpp
   Employee.hpp
   Manager.cpp
   Manager.hpp
   Director.cpp
   Director.hpp
)
