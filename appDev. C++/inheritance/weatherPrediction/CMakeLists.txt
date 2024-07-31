cmake_minimum_required(VERSION 3.28)
project(weatherPrediction)

set(CMAKE_CXX_STANDARD 23)

add_executable(weatherPrediction main.cpp
        WeatherPrediction.cpp
        WeatherPrediction.hpp
        MyWeatherPrediction.cpp
        MyWeatherPrediction.hpp)
