cmake_minimum_required (VERSION 3.5)
project (linear_ds)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

add_executable(test_list test_list.cpp list.hpp list_imp.hpp)
add_executable(test_stack test_stack.cpp stack.hpp stack_imp.hpp list.hpp
    list_imp.hpp)
add_executable(test_cdarray test_cdarray.cpp cdarray_imp.hpp)
add_executable(test_queue test_queue.cpp queue.hpp queue_imp.hpp
    stack.hpp stack_imp.hpp)

