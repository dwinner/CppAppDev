cmake_minimum_required(VERSION 3.29)
project(map_bankAccount)

set(CMAKE_CXX_STANDARD 23)

add_executable(map_bankAccount main.cpp
        BankAccount.hpp
        BankDB.cpp
        BankDB.hpp)
