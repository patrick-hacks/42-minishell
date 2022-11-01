/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:59 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:25:45 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "lib/execute/execute.h"
#include "lib/get_next_line/get_next_line.h"
#include "lib/libft/libft.h"
#include "lib/parse/parse.h"
#include "src/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>

void	heredoc_child(t_cmd *c, int fd);

void	heredoc_replace_helper(t_cmd *c, char *file_name, int *ret)
{
	free(c->redirect_input->str);
	c->redirect_input->str = file_name;
	waitpid(-1, ret, 0);
	set_signal(SIG_READLINE);
}

void	heredoc_replace_helper_child(t_cmd *c, int fd)
{
	set_signal(SIG_HEREDOC_CHILD);
	set_termios(1);
	heredoc_child(c, fd);
	exit(0);
}
