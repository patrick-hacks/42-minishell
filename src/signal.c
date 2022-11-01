/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:17:09 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 04:47:25 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "src/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>

void	empty(int signo)
{
	(void)signo;
}

void	signal_ctlc(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		environ_add("?=130");
	}
}

void	sigint_handler_print_newline(int signo)
{
	environ_add("?=130");
	if (signo == SIGINT)
		write(2, "\n", 1);
}

void	set_signal(int sig)
{
	signal(SIGQUIT, SIG_DFL);
	if (sig == SIG_SUBSHELL)
		signal(SIGINT, SIG_IGN);
	if (sig == SIG_READLINE)
		signal(SIGINT, signal_ctlc);
	if (sig == SIG_HEREDOC)
		signal(SIGINT, sigint_handler_print_newline);
	if (sig == SIG_HEREDOC_CHILD)
		signal(SIGINT, SIG_DFL);
	if (sig == SIG_EXE)
		signal(SIGINT, SIG_DFL);
}

void	set_termios(int mode)
{
	struct termios	term_setting;

	tcgetattr(STDOUT_FILENO, &term_setting);
	if (mode == 1)
		term_setting.c_lflag &= ~(ECHOCTL);
	else
		term_setting.c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, 0, &term_setting);
}
