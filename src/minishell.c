/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:17:04 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:08:36 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "lib/execute/execute.h"
#include "lib/get_next_line/get_next_line.h"
#include "lib/libft/libft.h"
#include "lib/parse/parse.h"
#include "lib/tokenize/tokenize.h"
#include "src/minishell.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

// extern int(*rl_signal_event_hook)();

// int rl_signal() {
//   environ_add("?=130");
//   write(1, "\n", 1);
//   rl_set_prompt("\e[1;31m130\xE2\x9E\x9C\e[0m ");
//   rl_on_new_line();
//   rl_redisplay();
//   return (0);
// }

static char	*pretty_readline(void)
{
	char	*line;
	char	*ret;
	char	prompt[20];

	set_signal(SIG_READLINE);
	if (!isatty(0))
		return (get_next_line(0));
	line = "";
	while (!line[0])
	{
		ret = environ_get("?");
		ft_strcpy(prompt, "\e[1;32m:) \xE2\x9E\x9C\e[0m ");
		if (ret && ret[0] != '0' && ft_strlen(ret) <= 5)
		{
			ft_strcpy(prompt, "\e[1;31m   \xE2\x9E\x9C\e[0m ");
			ft_memcpy(prompt + 7, ret, ft_strlen(ret));
		}
		line = readline(prompt);
		if (!line)
			return (NULL);
	}
	add_history(line);
	return (line);
}

static int	bonus(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->flags & (TOK_AND | TOK_OR | TOK_BRACKET))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	minishell(void)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*commands;
	int		ret;

	environ_init();
	while (1)
	{
		line = pretty_readline();
		if (!line)
			break ;
		tokens = tokenize(line);
		free(line);
		if (!tokens || bonus(tokens))
			continue ;
		parse_expand_token(tokens);
		commands = parse(tokens);
		if (heredoc_replace(commands) == 0)
			execute(commands);
		heredoc_cleanup(commands);
		parse_lst_free(&commands);
	}
	ret = ft_atoi(environ_get("?"));
	environ_cleanup();
	return (ret);
}
