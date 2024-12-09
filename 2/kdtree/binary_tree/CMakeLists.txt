cmake_minimum_required (VERSION 3.1)
project (binary_tree VERSION 1.7 LANGUAGES CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3")
include_directories(".")

add_executable(test_btree_node test_btree_node.cpp btree.hpp btree_imp.hpp)
add_executable(test_btree test_btree.cpp btree.hpp btree_imp.hpp
    btree_utils.hpp btree_utils_imp.hpp)
