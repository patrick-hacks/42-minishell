#include "lib/environ/environ.h"
#include "lib/execute/src/execute.h"

int cmd_env(cmd *c, int *fd) {
  (void) c;
  (void) fd;
  environ_print();
  return 0;
}
