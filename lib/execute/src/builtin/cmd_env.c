#include "lib/environ/environ.h"
#include "lib/execute/src/execute.h"
#include <stdio.h>

int cmd_env(cmd *c, int *fd) {
  (void) c;
  (void) fd;
  int i = 0;
	while (g_environ[i])
	{
    dprintf(fd[1], "%s\n", g_environ[i]);
		i++;
	}
	return (0);
}