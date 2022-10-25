/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or_die.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:52 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:44 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/execute/src/execute.h"
#include "lib/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	fork_or_die(void)
{
	int	pid;

	if (getenv("DEBUG"))
	{
		fprintf(stderr, "\e[0;43mforking\e[0m\n");
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (getenv("DEBUG"))
	{
		fprintf(stderr, "    child pid: %d\n", pid);
	}
	return (pid);
}

void	pipe_or_die(int pipe_fd[2])
{
	int	err;

	err = pipe(pipe_fd);
	if (getenv("DEBUG"))
	{
		fprintf(stderr, "pipe: %d==%d\n", pipe_fd[0], pipe_fd[1]);
	}
	if (err == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	close_or_die(int fd)
{
	int	err;

	if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == -1)
		return ;
	if (getenv("DEBUG"))
	{
		fprintf(stderr, "closing fd: %d\n", fd);
	}
	err = close(fd);
	if (err)
	{
		perror("close");
		exit(1);
	}
}

void	execve_or_die(char *cmd, char **argv, char **env)
{
		char sys[200];

	if (getenv("DEBUG"))
	{
		snprintf(sys, 200, "echo '%1$d' >&2; ls -l /proc/%1$d/fd >&2",
				getpid());
		system(sys);
		sleep(1);
	}
	execve(cmd, argv, env);
	perror("execve");
	//execve("/bin/true", argv, env);
	exit(126);
}
