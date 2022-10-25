/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:59 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:27 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "lib/execute/execute.h"
#include "lib/get_next_line/get_next_line.h"
#include "lib/libft/libft.h"
#include "lib/parse/parse.h"
#include "src/minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>

static int	create_tmpfile(char *filename, int size)
{
	int		i;
	char	*nbr;
	int		fd;

	i = 0;
	while (1)
	{
		ft_strncpy(filename, "/tmp/mini", size);
		nbr = ft_itoa(i);
		ft_strlcat(filename, nbr, size);
		free(nbr);
		if (access(filename, F_OK) == -1)
			break ;
		i += 1;
	}
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	return (fd);
}

static void	read_to_fd(int fd, char *delim, bool quoted)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!line || ft_strncmp(line, delim, ft_strlen(delim)) == 0)
			break ;
		if (!quoted)
			parse_expand_str(&line);
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

static void	heredoc_child(cmd *c, int fd)
{
	char	*delim;

	while (c)
	{
		if (c->redirect_input && c->redirect_input->flags & TOK_HEREDOC)
		{
			delim = c->redirect_input->str;
			read_to_fd(
				fd, delim,
					c->redirect_input->flags & (TOK_DOUBLE_QUOTED | TOK_SINGLE_QUOTED));
			close(fd);
		}
		c = c->next;
	}
}

int	heredoc_replace(cmd *c)
{
	char	*file_name;
	int		fd;
			int ret;
	int		pid;

	while (c)
	{
		if (c->redirect_input && c->redirect_input->flags & TOK_HEREDOC)
		{
			file_name = ft_calloc_or_die(1, 30);
			fd = create_tmpfile(file_name, 30);
			set_signal(SIG_HEREDOC);
			pid = fork();
			if (pid == -1)
				exit(1);
			if (pid == 0)
			{
				set_signal(SIG_HEREDOC_CHILD);
				set_termios(1);
				heredoc_child(c, fd);
				exit(0);
			}
			free(c->redirect_input->str);
			c->redirect_input->str = file_name;
			waitpid(-1, &ret, 0);
			set_signal(SIG_READLINE);
			if (WIFSIGNALED(ret) || !WIFEXITED(ret) || WEXITSTATUS(ret) != 0)
			{
				environ_add("?=130");
				return (1);
			}
		}
		c = c->next;
	}
	return (0);
}

void	heredoc_cleanup(cmd *c)
{
	while (c)
	{
		if (c->redirect_input && c->redirect_input->flags & TOK_HEREDOC)
		{
			remove(c->redirect_input->str);
		}
		c = c->next;
	}
}
