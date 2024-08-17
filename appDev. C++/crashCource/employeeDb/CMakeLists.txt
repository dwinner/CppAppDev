cmake_minimum_required(VERSION 3.28)
project(employeeDb)

set(CMAKE_CXX_STANDARD 23)

add_executable(employeeDb main.cpp
        Employee.cpp
		Employee.hpp
        Database.cpp
		Database.hpp
)
