cmake_minimum_required(VERSION 3.14)
project(send_mail C)

set(CMAKE_C_STANDARD 11)

add_executable(send_mail main.c network.h send_email.c send_email.h)