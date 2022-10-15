
#include <fcntl.h>
#include <limits.h>  // PATH_MAX
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib/environ/environ.h"
#include "lib/execute/src/execute.h"
#include "lib/libft/libft.h"

static char *find_correct_path(char *cmd, char **split) {
  char test_cmd[PATH_MAX];
  test_cmd[0] = '\0';
  while (*split) {
    ft_strlcpy(test_cmd, *split, PATH_MAX - 1);
    ft_strlcat(test_cmd, "/", PATH_MAX - 1);
    ft_strlcat(test_cmd, cmd, PATH_MAX - 1);
    if (access(test_cmd, X_OK) == 0) {
      char *result = ft_calloc_or_die(1, ft_strlen(test_cmd) + 1);
      ft_strcpy(result, test_cmd);
      return result;
    }
    split++;
  }
  return (0);
}

char *find_command(char *cmd) {
  if (!cmd[0])
    return 0;
  char *result = 0;
  char *paths = environ_get("PATH");
  if (paths) {
    char **split = ft_strsplit(paths, ':');
    result = find_correct_path(cmd, split);
    ft_free_pointer_array((void **)split);
  }
  return result;
}

int get_argc(cmd *command) {
  token *it = command->simple_cmd;
  int i = 0;
  while (it) {
    i += 1;
    it = it->next;
  }
  return i;
}

char **get_argv(cmd *c) {
  char **argv = ft_calloc_or_die(get_argc(c) + 1, sizeof(char *));
  token *it = c->simple_cmd;
  int i = 0;
  while (it) {
    argv[i] = it->str;
    it = it->next;
    i += 1;
  }
  return (argv);
}
