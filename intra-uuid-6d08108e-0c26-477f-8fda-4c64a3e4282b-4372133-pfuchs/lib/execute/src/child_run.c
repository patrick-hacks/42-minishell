/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:48 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:05:46 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "lib/execute/src/builtin/builtin.h"
#include "lib/execute/src/p_execute.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	child_exec(t_cmd *c)
{
	char	*cmd;

	cmd = find_command(c->simple_cmd->str);
	if (cmd)
	{
		execve_or_die(cmd, get_argv(c), g_environ);
	}
	fprintf(stderr, "command not found\n");
	exit(127);
}

void	child_run(t_cmd *c, int *fd)
{
	child_redirect(c, fd);
	close_or_die(fd[2]);
	child_exec(c);
}

int	child_run_builtin(t_cmd *c, int *fd)
{
	t_builtin_main	main;

	main = get_builtin(c->simple_cmd->str);
	child_redirect_builtin(c, fd);
	return (main(c, fd));
}
