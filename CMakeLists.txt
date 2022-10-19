cmake_minimum_required(VERSION 3.18)
project(minishell C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#add_compile_options("-Wall -Wextra -Wpedantic -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")


include_directories(.)

add_subdirectory(lib)
add_subdirectory(src)
