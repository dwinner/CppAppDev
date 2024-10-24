cmake_minimum_required(VERSION 3.29)
project(phoneBook)

set(CMAKE_CXX_STANDARD 23)

add_executable(phoneBook main.cpp
        Person.cpp
        Person.hpp
        PhoneBook.cpp
        PhoneBook.hpp
        NoSuchPerson.hpp)
