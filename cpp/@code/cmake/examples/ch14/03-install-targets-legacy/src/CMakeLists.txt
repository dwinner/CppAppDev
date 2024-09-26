add_library(calc STATIC basic.cpp)
target_include_directories(calc PUBLIC include)
set_target_properties(calc PROPERTIES
    PUBLIC_HEADER include/calc/basic.h
)