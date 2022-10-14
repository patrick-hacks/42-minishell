#include <limits.h>  // PATH_MAX
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "lib/environ/environ.h"
#include "lib/execute/src/execute.h"
#include "lib/libft/libft.h"

int chdir_error(const char *str) {
  int error = chdir(str);
  if (error) {
    perror("chdir");
    return 1;
  }
  char pwd[PATH_MAX];
  if (getcwd(pwd, PATH_MAX)) {
    fprintf(stderr, "could not determine directory\n");
		return 1;
  }
  char *key_set = ft_calloc_or_die(1, ft_strlen(pwd) + 5);
  ft_strcpy(key_set, pwd);
  ft_strlcat(key_set, "PWD=", ft_strlen(pwd) + 5);
  environ_add(key_set);
  free(key_set);
  return -1;
}

int cmd_cd(cmd *c, int *fd) {
  (void) fd;
  token *first = c->simple_cmd;
  if (!first) {
    const char *home = environ_get("HOME");
    printf("home is: -%s-", home);
    if (!home || *home == '\0') return chdir_error("/");
    return chdir_error(home);
  }
  if (first->next) {
    fprintf(stderr, "cd: too many arguments");
    return 1;
  }
  return chdir_error(first->str);
}
