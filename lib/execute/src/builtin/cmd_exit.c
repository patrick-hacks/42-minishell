#include <stdlib.h>

#include "lib/execute/src/execute.h"
#include "lib/libft/libft.h"
#include "lib/environ/environ.h"

int cmd_exit(cmd *c, int *fd) {

  int return_code = 0;
  if (c->simple_cmd->next && c->simple_cmd->next->str) {
    return_code = ft_atoi(c->simple_cmd->next->str);
  }
  parse_lst_free(&c);
  environ_cleanup();
  close_or_die(fd[0]);
  close_or_die(fd[1]);
  close_or_die(fd[2]);
  exit(return_code);
}
