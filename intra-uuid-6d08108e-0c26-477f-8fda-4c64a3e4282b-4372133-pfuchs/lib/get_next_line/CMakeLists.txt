add_library(get_next_line STATIC
  get_next_line.h
  get_next_line.c
)

target_link_libraries(get_next_line PRIVATE libft)
