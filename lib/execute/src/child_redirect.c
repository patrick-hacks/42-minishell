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
    dup2(in, 0);
    close_or_die(fd[0]);
  } else {
    if (fd[0] != 0)
      dup2(fd[0], 0);
  }
  int out = get_outfile(c->redirect_output);
  if (out != -1) {
    dup2(out, 1);
    close_or_die(fd[1]);
  } else {
    if (fd[1] != 1)
      dup2(fd[1], 1);
  }
}

// I think they dont need input
void child_redirect_builtin(cmd *c, int fd[2]) {
  (void) c;
  (void) fd;
  // int in = get_infile(c->redirect_input);
  // if (in != -1) {
  //   close_or_die(fd[0]);
  //   fd[0] = in;
  // }
  int out = get_outfile(c->redirect_output);
  if (out != -1) {
    close_or_die(fd[1]);
    fd[1] = out;
  }
}
