cmake_minimum_required(VERSION 3.15)
project(focus C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(src)
configure_file(testcase.txt testcase.txt COPYONLY)