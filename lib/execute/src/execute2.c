/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 05:31:07 by azakizad          #+#    #+#             */
/*   Updated: 2022/11/01 06:11:22 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "lib/execute/src/builtin/builtin.h"
#include "lib/execute/src/p_execute.h"
#include "lib/libft/libft.h"
#include "lib/parse/parse.h"
#include "lib/tokenize/tokenize.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>

int	execute_cmd(t_cmd *c)
{
	int	i;
	int	fd[3];
	int	*pids;

	i = 0;
	pids = ft_calloc_or_die(command_count(c) + 1, sizeof(int *));
	while (c != NULL)
	{
		set_pipe(c, fd);
		if (c->simple_cmd)
		{
			if (get_builtin(c->simple_cmd->str))
			{
				child_run_builtin(c, fd);
			}
			else
			{
				pids[i] = child_fork(c, fd);
				i += 1;
			}
		}
		c = c->next;
	}
	close_or_die(fd[0]);
	return (handle_wait_status(pids));
}

int	execute_fork(t_cmd *c)
{
	int	*pids;

	pids = ft_calloc_or_die(2, sizeof(int *));
	pids[1] = 0;
	pids[0] = fork_or_die();
	if (pids[0] == 0)
	{
		exit(execute_cmd(c));
	}
	return (handle_wait_status(pids));
}

int	execute(t_cmd *c)
{
	if (command_count(c) == 1)
	{
		signal(SIGINT, SIG_IGN);
		execute_cmd(c);
		signal(SIGINT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		execute_fork(c);
		signal(SIGINT, SIG_DFL);
	}
	return (0);
}
