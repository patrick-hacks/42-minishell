#include "lib/environ/environ.h"
#include "lib/execute/src/execute.h"

int cmd_unset(cmd *c, int *fd) {
  (void) fd;
  token *it = c->simple_cmd;
  it = it->next;
  if (it->str[0] == '\0')
    return 0;
  while (it) {
    environ_remove(it->str);
    it = it->next;
  }
  return 0;
}
