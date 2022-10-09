#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "lib/environ/environ.h"
#include "lib/execute/execute.h"
#include "lib/libft/libft.h"
#include "lib/parse/parse.h"

static int create_tmpfile(char *filename, int size) {
  int i = 0;
  while (1) {
    ft_strncpy(filename, "/tmp/mini", size);
    char *nbr = ft_itoa(i);
    ft_strlcat(filename, nbr, size);
    free(nbr);
    if (access(filename, F_OK) == -1)
      break;
    else
      perror("access");
    i += 1;
  }
  int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
  if (fd == -1) {
    perror("open");
    exit(1);
  }
  return fd;
}

static void read_to_fd(int fd, char *delim, bool expand) {
  const int max_length = 65536;
  char *line = ft_calloc_or_die(1, max_length);
  while (1) {
    // char *line = readline(">");
    // int len = strlen(line);
    int len = read(STDIN_FILENO, line, max_length - 1);
    if (len == 0) continue;
    if (len < 0) break;
    line[len] = '\0';
    if (ft_strncmp(line, delim, len - 1) == 0 && ft_strlen(delim) == len - 1)
      break;
    write(fd, line, len);
  }
  //  free(line);
}

static void heredoc_child(cmd *c, int fd) {
  while (c) {
    if (c->redirect_input && c->redirect_input->flags & TOK_HEREDOC) {
      char *delim = c->redirect_input->str;
      read_to_fd(
          fd, delim,
          c->redirect_input->flags & (TOK_DOUBLE_QUOTED | TOK_SINGLE_QUOTED));
      close(fd);
    }
    c = c->next;
  }
}

int heredoc_replace(cmd *c) {
  char file_name[30];
  cmd *it = c;
  while (c) {
    if (c->redirect_input && c->redirect_input->flags & TOK_HEREDOC) {
      char *file_name = ft_calloc_or_die(1, 30);
      int fd = create_tmpfile(file_name, 30);
      int ret;
      // signal?
      int pid = fork();
      if (pid == -1) exit(1);
      if (pid == 0) {
        // signal;
        heredoc_child(c, fd);
        exit(0);
      }
      free(c->redirect_input->str);
      c->redirect_input->str = file_name;
      waitpid(-1, &ret, 0);
      // signal?
      if (ret != 0) return ret;
    }
    c = c->next;
  }
  return 0;
}

void heredoc_cleanup(cmd *c) {
  while (c) {
    if (c->redirect_input && c->redirect_input->flags & TOK_HEREDOC) {
      remove(c->redirect_input->str);
    }
    c = c->next;
  }
}
