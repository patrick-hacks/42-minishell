add_library(execute STATIC
  src/builtin/builtin.c
  src/builtin/builtin.h
  src/builtin/cmd_cd.c
  src/builtin/cmd_echo.c
  src/builtin/cmd_env.c
  src/builtin/cmd_exit.c
  src/builtin/cmd_export.c
  src/builtin/cmd_pwd.c
  src/builtin/cmd_unset.c
  src/execute.c
  src/exec_or_die.c
  src/exev_util.c
  src/child_run.c
  src/child_redirect.c
)

target_link_libraries(execute PRIVATE libft environ tokenize parse)
