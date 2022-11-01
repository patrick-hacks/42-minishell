add_library(tokenize STATIC
  tokenize.h
  src/tokenize_debug.c
  src/tokenize_error.c
  src/tokenize_get.c
  src/tokenize_lst.c
  src/tokenize.c
  src/p_tokenize.h
)

target_link_libraries(tokenize PRIVATE libft environ)
