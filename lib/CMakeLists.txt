add_subdirectory(environ)
add_subdirectory(execute)
add_subdirectory(libft)
add_subdirectory(parse)
add_subdirectory(tokenize)

set(READLINE_LIBRARIES
  "${CMAKE_CURRENT_BINARY_DIR}/readline/libhistory.a"
  "${CMAKE_CURRENT_BINARY_DIR}/readline/libreadline.a"
)

add_custom_command(OUTPUT ${READLINE_LIBRARIES}
  COMMAND ./configure
  COMMAND make all
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/readline
)

# add_library(readline INTERFACE)
# target_link_libraries(readline INTERFACE libreadline.a)
# target_compile_options(readline INTERFACE "-ltinfo")
