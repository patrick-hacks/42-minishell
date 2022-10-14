add_executable(minishell
  main.c
  heredoc.c
  minishell.c
  minishell.h
  signal.c
)

target_link_libraries(minishell
  PRIVATE
  libft
  parse
  execute
  environ
  tokenize
  local_readline
)
