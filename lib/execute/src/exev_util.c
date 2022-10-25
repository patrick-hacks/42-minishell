/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exev_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:00 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:41 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lib/environ/environ.h"
#include "lib/execute/src/execute.h"
#include "lib/libft/libft.h"
#include <fcntl.h>
#include <limits.h> // PATH_MAX
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*find_correct_path(char *cmd, char **split)
{
	char	test_cmd[PATH_MAX];
	char	*result;

	test_cmd[0] = '\0';
	while (*split)
	{
		ft_strlcpy(test_cmd, *split, PATH_MAX - 1);
		ft_strlcat(test_cmd, "/", PATH_MAX - 1);
		ft_strlcat(test_cmd, cmd, PATH_MAX - 1);
		if (access(test_cmd, X_OK) == 0)
		{
			result = ft_calloc_or_die(1, ft_strlen(test_cmd) + 1);
			ft_strcpy(result, test_cmd);
			return (result);
		}
		split++;
	}
	return (0);
}

char	*find_command(char *cmd)
{
	char	*result;
	char	*paths;
	char	**split;

	if (!cmd[0])
		return (0);
	result = 0;
	paths = environ_get("PATH");
	if (paths && ft_strchr(cmd, '/') == NULL)
	{
		split = ft_strsplit(paths, ':');
		result = find_correct_path(cmd, split);
		ft_free_pointer_array((void **)split);
	}
	else
	{
		if (access(cmd, X_OK) == 0)
		{
			result = cmd;
		}
	}
	return (result);
}

int	get_argc(cmd *command)
{
	token	*it;
	int		i;

	it = command->simple_cmd;
	i = 0;
	while (it)
	{
		i += 1;
		it = it->next;
	}
	return (i);
}

char	**get_argv(cmd *c)
{
	char	**argv;
	token	*it;
	int		i;

	argv = ft_calloc_or_die(get_argc(c) + 1, sizeof(char *));
	it = c->simple_cmd;
	i = 0;
	while (it)
	{
		argv[i] = it->str;
		it = it->next;
		i += 1;
	}
	return (argv);
}
