cmake_minimum_required(VERSION 3.29)
project(staticSubscriptingOperator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_CXX_MODULE_STD 1)

add_executable(staticSubscriptingOperator main.cpp)

target_compile_features(staticSubscriptingOperator PRIVATE cxx_std_23)