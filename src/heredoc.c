#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include "lib/environ/environ.h"
#include "lib/execute/execute.h"
#include "lib/libft/libft.h"
#include "lib/parse/parse.h"
#include "src/minishell.h"

static int create_tmpfile(char *filename, int size) {
  int i = 0;
  while (1) {
    ft_strncpy(filename, "/tmp/mini", size);
    char *nbr = ft_itoa(i);
    ft_strlcat(filename, nbr, size);
    free(nbr);
    if (access(filename, F_OK) == -1) break;
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
  (void)expand;
  const int max_length = 65536;
  char *line = ft_calloc_or_die(1, max_length);
  while (1) {
    // char *line = readline(">");
    // int len = strlen(line);
    int len = read(STDIN_FILENO, line, max_length - 1);
    if (len == 0) continue;
    if (len < 0) break;
    line[len] = '\0';
    if (ft_strncmp(line, delim, len - 1) == 0 &&
        ft_strlen(delim) == (size_t)(len - 1))
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
  while (c) {
    if (c->redirect_input && c->redirect_input->flags & TOK_HEREDOC) {
      char *file_name = ft_calloc_or_die(1, 30);
      int fd = create_tmpfile(file_name, 30);
      int ret;
      signal(SIGINT, SIG_IGN);
      int pid = fork();
      if (pid == -1) exit(1);
      if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        heredoc_child(c, fd);
        exit(42);
      }
      free(c->redirect_input->str);
      c->redirect_input->str = file_name;
      waitpid(-1, &ret, 0);
      set_signal(SIG_DEFAULT);
      if (WIFSIGNALED(ret) || !WIFEXITED(ret) || WEXITSTATUS(ret) != 0) {
        environ_add("?=130");
        return 1;
      }
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
