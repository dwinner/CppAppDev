add_executable(calc_test basic_test.cpp)
target_link_libraries(calc_test PRIVATE calc_static)
AddTests(calc_test)