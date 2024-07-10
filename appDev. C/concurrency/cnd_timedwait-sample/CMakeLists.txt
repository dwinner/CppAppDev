cmake_minimum_required(VERSION 3.16)
project(cnd_timedwait_sample C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(cnd_timedwait_sample
        cnd_timedwait-sample.c)
