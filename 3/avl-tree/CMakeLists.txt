cmake_minimum_required (VERSION 3.5)
project (avl_tree VERSION 1.5 LANGUAGES CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3")


add_executable(test_bstree test_avltree.cpp avltree.hpp avltree_imp.hpp)
target_compile_definitions(test_bstree PRIVATE -D__ONLY_BSTREE__=1)

add_executable(test_avltree test_avltree.cpp avltree.hpp avltree_imp.hpp)
