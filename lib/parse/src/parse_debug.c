/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:16 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:06:32 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/parse/src/p_parse.h"
#include <stdio.h>

static void	debug_cmd_redirect(t_token *redir)
{
	while (redir)
	{
		printf("\033[1;42m");
		if (redir->flags & TOK_WRITE)
			printf(">");
		else if (redir->flags & TOK_APPEND)
			printf(">>");
		else if (redir->flags & TOK_READ)
			printf("<");
		else if (redir->flags & TOK_HEREDOC)
			printf("<<");
		else
			printf("WTF");
		if (redir->flags & (TOK_SINGLE_QUOTED | TOK_DOUBLE_QUOTED))
			printf(" \"%s\"\033[0;m |", redir->str);
		else
			printf(" %s\033[0;m |", redir->str);
		redir = redir->next;
	}
}

void	debug_cmd_print(t_cmd *command)
{
	t_token	*it;

	printf("\033[1;43m");
	printf("%-100s", "       Commands");
	printf("\033[0m\n");
	while (command)
	{
		it = command->simple_cmd;
		while (it)
		{
			if (it->str)
				printf("%s | ", it->str);
			else
				printf("no command :( | ");
			it = it->next;
		}
		debug_cmd_redirect(command->redirect_input);
		debug_cmd_redirect(command->redirect_output);
		command = command->next;
		printf("\n");
	}
}
