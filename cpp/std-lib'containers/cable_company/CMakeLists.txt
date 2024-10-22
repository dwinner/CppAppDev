cmake_minimum_required(VERSION 3.29)
project(cable_company)

set(CMAKE_CXX_STANDARD 23)

add_executable(cable_company main.cpp
        CableCompany.cpp
        CableCompany.hpp)
