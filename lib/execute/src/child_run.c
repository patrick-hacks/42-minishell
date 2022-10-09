#include "lib/environ/environ.h"
#include "lib/execute/src/execute.h"
#include "lib/execute/src/builtin/builtin.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void child_exec(cmd *c, int fd[2]) {
  char *cmd = find_command(c->simple_cmd->str);
  if (cmd) {
    execve_or_die(cmd, get_argv(c), g_environ);
  }
  fprintf(stderr, "command not found\n");
  execve_or_die("/bin/true", get_argv(c), g_environ);
}

void child_run(cmd *c, int *fd) {
  child_redirect(c, fd);
  close_or_die(fd[2]);
	child_exec(c, fd);
}

void child_run_builtin(cmd *c, int *fd) {
  builtin_main main = get_builtin(c->simple_cmd->str);
  // child_redirect_builtin(c, fd);
  // close_or_die(fd[2]);
  main(c, fd);
}
