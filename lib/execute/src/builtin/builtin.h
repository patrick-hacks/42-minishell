#ifndef LIB_EXECUTE_SRC_BUILTIN_BUILTIN_H_
#define LIB_EXECUTE_SRC_BUILTIN_BUILTIN_H_

#include "lib/execute/src/execute.h"

typedef int (*builtin_main)(cmd *c, int *fd);

builtin_main get_builtin(char *command);

#endif // LIB_EXECUTE_SRC_BUILTIN_BUILTIN_H_
