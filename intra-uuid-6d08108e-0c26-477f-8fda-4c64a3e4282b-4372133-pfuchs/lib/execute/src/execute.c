/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:55 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:10:42 by azakizad         ###   ########.fr       */
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

int	command_count(t_cmd *c)
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
	char	buf[20];
	char	*error_str;

	exit_status = wait_children(pids);
	if (WIFEXITED(exit_status))
		error = WEXITSTATUS(exit_status);
	else
		error = WCOREFLAG + WTERMSIG(exit_status);
	free(pids);
	buf[0] = '?';
	buf[1] = '=';
	buf[2] = '\0';
	error_str = ft_itoa(error);
	ft_strcat(buf, error_str);
	free(error_str);
	environ_add(buf);
	return (error);
}

int	child_fork(t_cmd *c, int *fd)
{
	int	pid;

	pid = fork_or_die();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		child_run(c, fd);
	}
	return (pid);
}

void	set_pipe(t_cmd *c, int fd[3])
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
