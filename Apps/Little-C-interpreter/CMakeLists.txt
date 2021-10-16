cmake_minimum_required(VERSION 3.16)
project(Little_C_interpreter C)

set(CMAKE_C_STANDARD 11)

add_executable(Little_C_interpreter main.c descent_parser.c descent_parser.h parser_types.h parser_utils.c parser_utils.h)