cmake_minimum_required(VERSION 3.10)
project(LinkedList C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-pthread")  # Ensure POSIX threads are linked

include_directories(inc)

add_executable(main src/main.c src/linked_list.c)
add_executable(test_linked_list test/test_linked_list.c src/linked_list.c)
