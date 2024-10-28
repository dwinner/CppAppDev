cmake_minimum_required(VERSION 3.29)
project(multimap_buddyList)

set(CMAKE_CXX_STANDARD 23)

add_executable(multimap_buddyList main.cpp
        BuddyList.cpp
        BuddyList.hpp)
