cmake_minimum_required (VERSION 3.1)
project (pattern VERSION 1.0 LANGUAGES CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3")
include_directories(".")

add_library(pattern STATIC pattern.cpp pattern.hpp)
add_executable(test_pattern test_pattern.cpp pattern)
