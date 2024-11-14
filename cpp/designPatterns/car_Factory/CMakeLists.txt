cmake_minimum_required(VERSION 3.29)
project(car_Factory)

set(CMAKE_CXX_STANDARD 23)

add_executable(car_Factory main.cpp
        Cars.hpp
        CarFactories.hpp
        LeastBusyFactory.hpp)
