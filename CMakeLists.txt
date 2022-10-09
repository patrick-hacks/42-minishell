cmake_minimum_required(VERSION 3.18)
project(minishell C)

set(CMAKE_VERBOSE_MAKEFILE off)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_compile_options("-g")

include_directories(.)

add_subdirectory(lib)
add_subdirectory(src)
