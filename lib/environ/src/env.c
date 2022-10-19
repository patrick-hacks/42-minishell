#include "lib/environ/src/environ.h"
#include "lib/libft/libft.h"

extern char **environ;
char **g_environ;

int environ_init(void) {
  int i;

  i = split_count(environ);
  if (i == 0) return (0);
  g_environ = ft_calloc_or_die(i + 1, sizeof(char *));
  i = 0;
  while (environ[i]) {
    g_environ[i] = ft_strsub_or_die(environ[i], 0, INT32_MAX);
    i++;
  }
  g_environ[i] = NULL;
  return (0);
}

char *environ_get(char *entry) {
  char *result = environ_find(entry);
  if (!result && ft_strncmp(entry, "IFS", 4) == 0) {
    return " \n\t";
  }
  if (result) {
	return (ft_strchr(result, '=') + 1);
  }
  return (NULL);
}

char *environ_find(char *name) {
  int l_name;
  int i;

  if (ft_strchr(name, '='))
    l_name = ft_strchr(name, '=') - name;
  else
    l_name = ft_strlen(name);
  i = 0;
  while (g_environ[i]) {
    if (!ft_strncmp(name, g_environ[i], l_name) && g_environ[i][l_name] == '=')
      return (g_environ[i]);
    i++;
  }
  return (NULL);
}

int environ_is_value(char *var_name, char *value) {
  char *env_value;

  env_value = environ_get(var_name);
  if (env_value)
    if (ft_strncmp(env_value, value, ft_strlen(value) + 1) == 0) return (1);
  return (0);
}

int env_is_var_char(char c) { return (ft_isalnum(c) || c == '_'); }
