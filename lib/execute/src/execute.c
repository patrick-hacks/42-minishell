#include "lib/execute/src/execute.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include "lib/execute/src/builtin/builtin.h"
#include "lib/libft/libft.h"
#include "lib/parse/parse.h"
#include "lib/tokenize/tokenize.h"

int wait_children(int *pids) {
  int exit_status;
  exit_status = 0;
  while (*pids) {
    waitpid(*pids, &exit_status, 0);
    pids++;
  }
  return (exit_status);
}

static int command_count(cmd *c) {
  int i = 0;
  while (c) {
    c = c->next;
    i += 1;
  }
  return i;
}

int handle_wait_status(int *pids) {
  int exit_status;
  int error;

  exit_status = wait_children(pids);
  if (WIFEXITED(exit_status))
    error = WEXITSTATUS(exit_status);
  else
    error = WCOREFLAG + WTERMSIG(exit_status);
  free(pids);
  return (error);
}

int child_fork(cmd *c, int *fd) {
  // signal?
  int pid = fork_or_die();
  if (pid == 0) {
    signal(SIGINT, SIG_DFL);
    child_run(c, fd);
  }
  return (pid);
}

void set_pipe(cmd *c, int fd[3]) {
  if (!c->prev) {
    fd[0] = STDIN_FILENO;
    fd[1] = -1;
    fd[2] = -1;
  } else {
    close_or_die(fd[0]);
    close_or_die(fd[1]);
    fd[0] = fd[2];
  }
  if (!c->next) {
    fd[1] = STDOUT_FILENO;
  } else {
    pipe_or_die(fd + 1);
    int tmp = fd[1];
    fd[1] = fd[2];
    fd[2] = tmp;
  }
}

int execute_cmd(cmd *c) {
  int i = 0;
  int fd[3];
  int *pids = ft_calloc_or_die(command_count(c) + 1, sizeof(int));
  while (c != NULL) {
    set_pipe(c, fd);
    if (get_builtin(c->simple_cmd->str)) {
      child_run_builtin(c, fd);
    } else {
      pids[i] = child_fork(c, fd);
      i += 1;
    }
    c = c->next;
  }
  close_or_die(fd[0]);
  return (handle_wait_status(pids));
}

int execute_fork(cmd *c) {
  int fake_fd[3] = {-1, -1, -1};
  int pid = fork_or_die();
  if (pid == 0) {
    execute_cmd(c);
    cmd_exit(c, fake_fd);
    exit(0);
  }
  waitpid(-1, NULL, 0);
  return (pid);
}

int execute(cmd *c) {
  if (command_count(c) == 1) {
    execute_cmd(c);
  } else {
    execute_fork(c);
  }
  return 0;
}
