add_library(parse STATIC
  parse.h
  src/parse_cmd.c
  src/parse_debug.c
  src/parse_expand.c
  src/parse_expand_2.c
  src/parse_free.c
  src/parse_token.c
  src/parse.c
  src/p_parse.h
)

target_link_libraries(parse PRIVATE libft tokenize)
