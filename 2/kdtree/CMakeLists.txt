cmake_minimum_required (VERSION 3.5)
project (kdtree VERSION 1.0 LANGUAGES CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3")
include_directories(".")

add_subdirectory(pattern)
include_directories("pattern")

add_subdirectory(binary_tree)
include_directories("binary_tree")

add_library(kdtree STATIC kdtree.hpp kdtree.cpp)
target_link_libraries(kdtree pattern)

add_executable(test_kdtree test_kdtree.cpp)
target_link_libraries(test_kdtree kdtree pattern)
#target_compile_definitions(test_kdtree PRIVATE -D__DEBUG__=1)
