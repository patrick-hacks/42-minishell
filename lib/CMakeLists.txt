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
                   COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/readline/
                   COMMAND cp libhistory.a libreadline.a ${CMAKE_CURRENT_BINARY_DIR}/readline/
                   COMMAND make clean
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/readline
)
add_library(readline ${READLINE_LIBRARIES})
set_target_properties(readline PROPERTIES LINKER_LANGUAGE C)
