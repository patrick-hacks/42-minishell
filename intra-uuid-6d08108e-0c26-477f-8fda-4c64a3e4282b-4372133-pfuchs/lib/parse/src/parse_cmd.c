/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:14 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:27:29 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "lib/parse/src/p_parse.h"
#include "lib/tokenize/tokenize.h"
#include <stdlib.h>

int	extract_redirection(t_cmd *cmd, t_token *tok)
{
	t_token	*name;
	t_token	*next;

	tok = cmd->simple_cmd;
	while (tok)
	{
		if (tok->flags & TOK_REDIRECT)
		{
			name = tok->next;
			if (!name || !name->str)
				return (1);
			next = name->next;
			name->flags |= tok->flags;
			token_lst_remove(&cmd->simple_cmd, name);
			if (tok->flags & (TOK_READ | TOK_HEREDOC))
				token_lst_push_back(&cmd->redirect_input, name);
			if (tok->flags & (TOK_WRITE | TOK_APPEND))
				token_lst_push_back(&cmd->redirect_output, name);
			token_free(token_lst_remove(&cmd->simple_cmd, tok));
			tok = next;
		}
		else
			tok = tok->next;
	}
	return (0);
}

t_cmd	*convert_to_command(t_token *tok)
{
	t_cmd		*head;
	t_cmd		*cmd_it;
	t_token		*next;

	head = ft_calloc_or_die(1, sizeof(t_cmd));
	head->simple_cmd = tok;
	cmd_it = head;
	while (tok != NULL)
	{
		next = tok->next;
		if (tok->flags & TOK_PIPE)
		{
			if (tok->prev)
				tok->prev->next = NULL;
			if (tok->next)
				tok->next->prev = NULL;
			token_free(tok);
			cmd_it->next = ft_calloc_or_die(1, sizeof(t_cmd));
			cmd_it->next->prev = cmd_it;
			cmd_it = cmd_it->next;
			cmd_it->simple_cmd = next;
		}
		tok = next;
	}
	return (head);
}
