#include <stdio.h>

#include "lib/environ/environ.h"
#include "lib/execute/src/execute.h"

static int is_valid_argument(char *arg) {
  int i;

  if (arg[0] == '\0' || arg[0] == '=') return 0;
  i = 0;
  while (arg[i] != '\0' && arg[i] != '=' && env_is_var_char(arg[i])) i++;
  if (arg[i] == '\0' || arg[i] == '=') return 1;
  return 1;
}

int cmd_export(cmd *c, int *fd) {
  (void)fd;
  token *it = c->simple_cmd->next;
  int error = 0;
  while (it) {
    if (!is_valid_argument(it->str)) {
      fprintf(stderr, "not a valid identifier");
      environ_add("?=1");
      error = 1;
    } else {
      environ_add(it->str);
    }
    it = it->next;
  }
  return error;
}
