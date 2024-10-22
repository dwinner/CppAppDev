cmake_minimum_required(VERSION 3.29)
project(set_aclSample)

set(CMAKE_CXX_STANDARD 23)

add_executable(set_aclSample main.cpp
        AccessList.hpp)
