add_library(tokenize STATIC
  tokenize.h
  src/tokenize_debug.c
  src/tokenize_error.c
  src/tokenize_get.c
  src/tokenize_lst.c
  src/tokenize_split.c
  src/tokenize.c
  src/tokenize.h
)

target_link_libraries(tokenize PRIVATE libft environ)
