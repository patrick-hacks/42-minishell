#include "lib/environ/environ.h"
#include "lib/execute/src/execute.h"

int cmd_env(cmd *c, int *fd) {
  environ_print();
  return 0;
}
