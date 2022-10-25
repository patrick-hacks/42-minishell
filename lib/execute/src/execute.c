/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:55 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:42 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "lib/execute/src/builtin/builtin.h"
#include "lib/execute/src/execute.h"
#include "lib/libft/libft.h"
#include "lib/parse/parse.h"
#include "lib/tokenize/tokenize.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>

int	wait_children(int *pids)
{
	int	exit_status;

	exit_status = 0;
	while (*pids)
	{
		waitpid(*pids, &exit_status, 0);
		pids++;
	}
	return (exit_status);
}

static int	command_count(cmd *c)
{
	int	i;

	i = 0;
	while (c)
	{
		c = c->next;
		i += 1;
	}
	return (i);
}

int	handle_wait_status(int *pids)
{
	int		exit_status;
	int		error;
	char	buf[10];
	char	*error_str;

	exit_status = wait_children(pids);
	if (WIFEXITED(exit_status))
		error = WEXITSTATUS(exit_status);
	else
		error = WCOREFLAG + WTERMSIG(exit_status);
	free(pids);
	buf[10] = "?=";
	error_str = ft_itoa(error);
	ft_strcat(buf, error_str);
	free(error_str);
	environ_add(buf);
	return (error);
}

int	child_fork(cmd *c, int *fd)
{
	int	pid;

	// signal?
	pid = fork_or_die();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		child_run(c, fd);
	}
	return (pid);
}

void	set_pipe(cmd *c, int fd[3])
{
	int	tmp;

	if (!c->prev)
	{
		fd[0] = STDIN_FILENO;
		fd[1] = -1;
		fd[2] = -1;
	}
	else
	{
		close_or_die(fd[0]);
		close_or_die(fd[1]);
		fd[0] = fd[2];
	}
	if (!c->next)
	{
		fd[1] = STDOUT_FILENO;
	}
	else
	{
		pipe_or_die(fd + 1);
		tmp = fd[1];
		fd[1] = fd[2];
		fd[2] = tmp;
	}
}

int	execute_cmd(cmd *c)
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

int	execute_fork(cmd *c)
{
	int	*pids;

	// int fake_fd[3] = {-1, -1, -1};
	pids = ft_calloc_or_die(2, sizeof(int *));
	pids[1] = 0;
	pids[0] = fork_or_die();
	if (pids[0] == 0)
	{
		exit(execute_cmd(c));
		// get_builtin("exit")(c, fake_fd);
		// exit(0);
	}
	// waitpid(-1, NULL, 0);
	return (handle_wait_status(pids));
}

int	execute(cmd *c)
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
