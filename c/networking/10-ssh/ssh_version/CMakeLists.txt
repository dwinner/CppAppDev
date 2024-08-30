cmake_minimum_required(VERSION 3.14)
project(ssh_version C)

set(CMAKE_C_STANDARD 11)

add_executable(ssh_version main.c ssh_network.h)

target_link_libraries(ssh_version ssh)