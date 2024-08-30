cmake_minimum_required(VERSION 3.28)
project(milesEstimator)

set(CMAKE_CXX_STANDARD 23)

add_executable(milesEstimator main.cpp
        MilesEstimator.hpp
        EfficientCarMilesEstimator.hpp)
