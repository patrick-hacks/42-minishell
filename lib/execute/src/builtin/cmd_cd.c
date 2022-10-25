/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:28 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:51 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "lib/execute/src/execute.h"
#include "lib/libft/libft.h"
#include <limits.h> // PATH_MAX
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	chdir_error(const char *str)
{
	int		error;
	char	pwd[PATH_MAX];
	char	*key_set;

	error = chdir(str);
	if (error)
	{
		perror("chdir");
		return (1);
	}
	if (getcwd(pwd, PATH_MAX) == 0)
	{
		fprintf(stderr, "could not determine directory\n");
		return (1);
	}
	key_set = ft_calloc_or_die(1, ft_strlen(pwd) + 5);
	ft_strcpy(key_set, pwd);
	ft_strlcat(key_set, "PWD=", ft_strlen(pwd) + 5);
	environ_add(key_set);
	free(key_set);
	return (-1);
}

int	cmd_cd(cmd *c, int *fd)
{
	token		*first;
	const char	*home;

	(void)fd;
	first = c->simple_cmd->next;
	if (!first)
	{
		home = environ_get("HOME");
		if (!home || *home == '\0')
			return (chdir_error("/"));
		return (chdir_error(home));
	}
	if (first->next)
	{
		fprintf(stderr, "cd: too many arguments");
		return (1);
	}
	return (chdir_error(first->str));
}

// static char	*get_dir(int argc, char **argv);
// static int	update_pwd(void);

// int	builtin_cd(int argc, char **argv)
// {
// 	char	*dir;

// 	dir = argv[1];
// 	if (dir == NULL)
// 		return (EXIT_FAILURE);
// 	if (chdir(dir) == -1)
// 	{
// 		print_error_errno(SHELL_NAME, "cd", dir);
// 		return (EXIT_FAILURE);
// 	}
// 	if (argv[1] && ft_strncmp(argv[1], "-", 2) == 0)
// 		ft_putendl_fd(dir, STDOUT_FILENO);
// 	if (update_pwd() == ERROR)
// 		return (EXIT_FAILURE);
// 	return (0);
// }

// static int	update_pwd(void)
// {
// 	char	buf[PATH_MAX];

// 	if (environ_get("PWD"))
// 	{
// 		if (environ_set("OLDPWD", environ_get("PWD")) == ERROR)
// 			return (ERROR);
// 	}
// 	else
// 		envurin_remove("OLDPWD");
// 	if (getcwd(buf, sizeof(buf)) == NULL)
// 	{
// 		print_error_errno(SHELL_NAME, "cd", NULL);
// 		return (ERROR);
// 	}
// 	if (environ_set("PWD", buf) == ERROR)
// 		return (ERROR);
// 	return (0);
// }
