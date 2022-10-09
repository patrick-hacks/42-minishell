#include "lib/environ/environ.h"
#include "lib/execute/src/execute.h"

int cmd_export(cmd *c, int *fd) {
  token *it = c->simple_cmd;
  while (it) {
    environ_add(it->str);
    it = it->next;
  }
  return 0;
}
