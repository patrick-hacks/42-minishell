add_library(environ STATIC
  environ.h
  src/env.c
  src/env_util.c
  src/env_modify.c
)

target_link_libraries(environ PRIVATE libft)
