cmake_minimum_required (VERSION 3.5)
project (vector2d)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(test_vector2d test_vector2d.cpp vector2d.hpp vector2d_imp.hpp)

