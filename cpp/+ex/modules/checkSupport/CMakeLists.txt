cmake_minimum_required(VERSION 3.29)
project(checkSupport CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)

add_library(math)
target_sources(math
        PUBLIC FILE_SET CXX_MODULES FILES math.ixx
)
target_compile_features(math PUBLIC cxx_std_20)
set_target_properties(math PROPERTIES CXX_EXTENSIONS OFF)

add_executable(checkSupport main.cpp)
target_link_libraries(checkSupport PRIVATE math)