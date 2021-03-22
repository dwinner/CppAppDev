cmake_minimum_required(VERSION 3.12)
project(sm_stub C)

set(CMAKE_C_STANDARD 11)

add_executable(sm_stub main.c stub_fsm.c stub_fsm.h sm-utils.c sm-utils.h)