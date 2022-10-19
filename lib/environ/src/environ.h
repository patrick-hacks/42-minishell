#ifndef LIB_ENVIRON_SRC_ENVIRON_H_
#define LIB_ENVIRON_SRC_ENVIRON_H_

#include <stdlib.h>

#include "lib/environ/environ.h"

extern char **g_environ;

int split_count(char **split);
int split_append_str(char ***split, char *new_str);
int split_remove_str(char ***split, char *remove_str);
int split_replace_str(char ***split, char *old_str, char *new_str);
void split_sort(char **split);

int environ_init(void);
char *environ_get(char *entry);
char *environ_find(char *name);
int environ_is_value(char *var_name, char *value);
int env_is_var_char(char c);

#endif  // LIB_ENVIRON_SRC_ENVIRON_H_

