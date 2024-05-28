cmake_minimum_required(VERSION 3.28)
project(airlineTicket)

set(CMAKE_CXX_STANDARD 23)

add_executable(airlineTicket main.cpp
        AirlineTicket.cpp
        AirlineTicket.h)
