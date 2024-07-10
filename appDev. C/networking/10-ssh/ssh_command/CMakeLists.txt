cmake_minimum_required(VERSION 3.14)
project(ssh_command C)

set(CMAKE_C_STANDARD 11)

add_executable(ssh_command main.c ssh_network.h)

target_link_libraries(ssh_command ssh)