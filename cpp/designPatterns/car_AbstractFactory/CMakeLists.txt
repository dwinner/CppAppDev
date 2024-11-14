cmake_minimum_required(VERSION 3.29)
project(car_AbstractFactory)

set(CMAKE_CXX_STANDARD 23)

add_executable(car_AbstractFactory main.cpp
        ICar.hpp
        ICarFactory.hpp
        Ford.hpp
        Toyota.hpp
        FordFactory.hpp
        ToyotaFactory.hpp)
