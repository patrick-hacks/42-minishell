#include <limits.h>  // PATH_MAX
#include <stdio.h>   // printf
#include <unistd.h>  // getcwd

#include "lib/execute/src/execute.h"

int cmd_pwd(cmd *c, int *fd) {
  (void) c;
  (void) fd;
  char cwd[PATH_MAX];

  cwd[0] = '\0';
  if (getcwd(cwd, PATH_MAX) == NULL) {
    fprintf(stderr, "could not determine directory\n");
    return 1;
  }
  printf("%s\n", cwd);
  return 0;
}