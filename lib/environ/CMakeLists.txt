add_library(environ STATIC
  environ.h
  src/environ_2.c
  src/environ.c
)

target_link_libraries(environ PRIVATE libft)
