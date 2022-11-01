/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:42 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 09:42:53 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/tokenize/src/p_tokenize.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool	is_range_correct(char *line)
{
	if (!line)
		return (false);
	while (*line)
	{
		if (*line == '\'')
			line = ft_strchr(line + 1, '\'');
		else if (*line == '\"')
			line = ft_strchr(line + 1, '\"');
		else if (*line == '(')
			line = ft_strchr(line + 1, ')');
		else if (*line == ')')
			return (false);
		if (!line)
			return (false);
		line++;
	}
	return (true);
}

static bool	is_first_valid(t_token *t)
{
	if (t->flags & TOK_WORD)
		return (true);
	if (t->flags & TOK_REDIRECT)
		return (true);
	return (false);
}

static bool	is_center_valid(t_token *t)
{
	if (t->prev->flags & TOK_REDIRECT)
	{
		if (t->flags & TOK_WORD)
			return (true);
		return (false);
	}
	if (t->prev->flags & TOK_BRACKET)
	{
		if (t->flags & TOK_CONNECTOR)
			return (true);
		return (false);
	}
	if (t->prev->flags & TOK_CONNECTOR)
	{
		if (t->flags & TOK_BRACKET)
			return (true);
		if (t->flags & TOK_WORD)
			return (true);
		return (false);
	}
	return (true);
}

static bool	is_last_valid(t_token *t)
{
	if (t->flags & TOK_WORD)
		return (true);
	return (false);
}

bool	is_token_sequence_valid(t_token *t)
{
	if (!t)
		return (true);
	if (!is_first_valid(t))
		return (false);
	while (t->next)
	{
		t = t->next;
		if (!is_center_valid(t))
			return (false);
	}
	if (!is_last_valid(t))
		return (false);
	return (true);
}
