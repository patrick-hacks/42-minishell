#include "lib/environ/environ.h"
#include "lib/execute/src/execute.h"

int cmd_unset(cmd *c, int *fd) {
  token *it = c->simple_cmd;
  while (it) {
    environ_remove(it->str);
    it = it->next;
  }
  return 0;
}
