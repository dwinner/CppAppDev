cmake_minimum_required(VERSION 3.27)
project(expertSystems C)

set(CMAKE_C_STANDARD 23)

add_executable(expertSystems main.c
        common.h
        timers.c
        timers.h
        ruleFire.c
        ruleFire.h
        ruleChk.c
        ruleChk.h
        parser.c
        parser.h)
