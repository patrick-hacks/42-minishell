#include "lib/environ/src/environ.h"
#include "lib/libft/libft.h"
#include <stdlib.h>

int	environ_remove(char *name)
{
	char	*env_var;

	env_var = environ_find(name);
	if (env_var == NULL)
		return (1);
	split_remove_str(&g_environ, env_var);
	return (0);
}

int	environ_add(char *str)
{
	char	*old_var;
	char	*new_var;
	int		status;

	if (str == NULL || ft_strchr(str, '=') == NULL)
		return (1);
	new_var = ft_strsub_or_die(str, 0, INT32_MAX);
	old_var = environ_find(str);
	status = split_replace_str(&g_environ, old_var, new_var);
	if (status == 1)
	{
		status = split_append_str(&g_environ, new_var);
	}
	return (0);
}

int	environ_set(char *name, char *value)
{
	char	*var_str;
	char	*tmp;
	int		status;

	if (name == NULL || value == NULL)
		return (1);
	tmp = ft_strjoin(name, "=");
	var_str = ft_strjoin(tmp, value);
	free(tmp);
	status = environ_add(var_str);
	free(var_str);
	return (status);
}

void environ_cleanup() {}
