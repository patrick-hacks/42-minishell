#include "lib/execute/src/builtin/builtin.h"
#include "lib/libft/libft.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct s_command_function_pair {
  char *name;
  builtin_main function;
} command_function_pair;

int cmd_cd(cmd *c, int *fd);
int cmd_echo(cmd *c, int *fd);
int cmd_env(cmd *c, int *fd);
int cmd_exit(cmd *c, int *fd);
int cmd_export(cmd *c, int *fd);
int cmd_pwd(cmd *c, int *fd);
int cmd_unset(cmd *c, int *fd);

static const command_function_pair commands[] = {
    {"cd", cmd_cd},         {"echo", cmd_echo}, {"env", cmd_env}, {"exit", cmd_exit},
    {"export", cmd_export}, {"pwd", cmd_pwd},   {"unset", cmd_unset}};

builtin_main get_builtin(char *command) {
  int i = 0;
  while (i < (int)(sizeof(commands) / sizeof(commands[0]))) {
    if (ft_strncmp(command, commands[i].name, 20) == 0)
      return (commands[i].function);
    i += 1;
  }
  return (NULL);
}
