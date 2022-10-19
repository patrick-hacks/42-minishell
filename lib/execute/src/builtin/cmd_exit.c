#include <stdlib.h>

#include "lib/execute/src/execute.h"
#include "lib/libft/libft.h"
#include "lib/environ/environ.h"

#include <stdio.h>

int cmd_exit(cmd *c, int *fd) {
  (void) fd;
  int return_code = 0;
  if (c->simple_cmd->next) {
    return_code = 255;
    char *return_str = c->simple_cmd->next->str;
    if (return_str) {
      if (return_str[0] >= '0' && return_str[0] <= '9') {
        return_code = ft_atoi(c->simple_cmd->next->str);
      }
    }
  }
  parse_lst_free(&c);
  environ_cleanup();
  if (getenv("DEBUG")) {
    fprintf(stderr, "\e[0;43mexit\e[0m\n");
  }
  exit(return_code);
}
