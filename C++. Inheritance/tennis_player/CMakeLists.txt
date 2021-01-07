cmake_minimum_required(VERSION 3.10)
project(tennis_player)

set(CMAKE_CXX_STANDARD 14)

add_executable(tennis_player main.cpp TableTennisPlayer.cpp TableTennisPlayer.h RatedPlayer.cpp RatedPlayer.h)