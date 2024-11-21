cmake_minimum_required(VERSION 3.26)
project(Calc VERSION 1.1.0 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(NoInSourceBuilds)

include(CTest)

add_subdirectory(src bin)
add_subdirectory(test)

include(Packaging)