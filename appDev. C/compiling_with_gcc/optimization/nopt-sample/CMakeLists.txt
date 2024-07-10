cmake_minimum_required(VERSION 3.16)
project(nopt_sample C)

set(CMAKE_C_STANDARD 11)

add_executable(nopt_sample main.c eval_parser.c eval_parser.h)