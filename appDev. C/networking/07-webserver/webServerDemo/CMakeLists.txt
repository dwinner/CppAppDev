cmake_minimum_required(VERSION 3.10)
project(webServerDemo C)

set(CMAKE_C_STANDARD 11)

add_executable(webServerDemo
	main.c
	network.h
	web_srv_api.c
	web_srv_api.h)