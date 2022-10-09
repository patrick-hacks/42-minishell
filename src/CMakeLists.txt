add_executable(minishell
  main.c
  heredoc.c
  minishell.c
  minishell.h
  signal.c
)

target_link_libraries(minishell
  PRIVATE
  readline
  libft
  parse
  execute
  environ
  tokenize
)
