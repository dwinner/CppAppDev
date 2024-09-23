cmake_minimum_required(VERSION 3.29)
project(3dPointSample)

set(CMAKE_CXX_STANDARD 23)

add_executable(3dPointSample main.cpp
        Point3D.cpp
        Point3D.hpp)
