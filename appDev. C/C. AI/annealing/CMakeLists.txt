cmake_minimum_required(VERSION 3.10)
project(Annealing C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Annealing
	"common.h"
	"emsapop.c"
	"emsapop.h"
	"entryPoint.c"
)
