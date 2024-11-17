cmake_minimum_required(VERSION 3.29)
project(networklibSample)

set(CMAKE_CXX_STANDARD 23)

add_executable(networklibSample main.cpp
        ConnectionHandle.hpp
        HostHandle.hpp
        networklib.cpp
        networklib.hpp
        HostRecord.hpp
        WebHost.hpp)
