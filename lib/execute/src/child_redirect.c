#include "lib/execute/src/execute.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

static int get_infile(token *input) {
  int fd = -1;
  while (input) {
    close_or_die(fd);
    fd = open(input->str, O_RDONLY);
    if (fd == -1) {
      perror(input->str);
      exit(1);
    }
    input = input->next;
  }
  return (fd);
}

static int get_outfile(token *output) {
  int fd = -1;
  while (output) {
    printf("found this file: %s\n", output->str);
    close_or_die(fd);
    if (output->flags & TOK_WRITE)
      fd = open(output->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (output->flags & TOK_APPEND)
      fd = open(output->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
      perror(output->str);
      exit(1);
    }
    output = output->next;
  }
  return (fd);
}

void child_redirect(cmd *c, int fd[2]) {
  int in = get_infile(c->redirect_input);
  if (in != -1) {
    printf("using the file as input\n");
    dup2(in, 0);
    close_or_die(fd[0]);
  } else {
    printf("using the fd %d as input\n", fd[0]);
    if (fd[0] != 0)
      dup2(fd[0], 0);
  }
  int out = get_outfile(c->redirect_output);
  if (out != -1) {
    printf("using the file as output\n");
    dup2(out, 1);
    close_or_die(fd[1]);
  } else {
    printf("using the fd %d as output\n", fd[1]);
    if (fd[1] != 1)
      dup2(fd[1], 1);
  }
}

void child_redirect_builtin(cmd *c, int fd[2]) {
  int in = get_infile(c->redirect_input);
  if (in != -1) {
    printf("using the file as input\n");
    close_or_die(fd[0]);
    fd[0] = in;
  } else {
    printf("using the fd %d as input\n", fd[0]);
  }
  int out = get_outfile(c->redirect_output);
  if (out != -1) {
    printf("using the file as output\n");
    close_or_die(fd[1]);
    fd[1] = out;
  } else {
    printf("using the fd %d as output\n", fd[1]);
  }
}
