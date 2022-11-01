cmake_minimum_required(VERSION 3.18)
project(minishell C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#add_compile_options("-Wall -Wextra -Wpedantic -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -Werror")

link_directories(~/goinfre/.brew/opt/readline/lib/)
link_directories(~/homebrew/opt/readline/lib/)

include_directories(.)

add_subdirectory(lib)
add_subdirectory(src)
