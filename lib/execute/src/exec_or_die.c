#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib/execute/src/execute.h"

int fork_or_die() {
  int pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(1);
  }
  return pid;
}

void pipe_or_die(int pipe_fd[2]) {
  int err = pipe(pipe_fd);
  if (err == -1) {
    perror("pipe");
    exit(1);
  }
}

void close_or_die(int fd) {
  fprintf(stderr, "closing fd: %d\n", fd);
  if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == -1) return;
  int err = close(fd);
  if (err) {
    perror("close");
    exit(1);
  }
}
