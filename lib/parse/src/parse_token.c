/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:22 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:36 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "lib/parse/src/parse.h"
#include "lib/tokenize/tokenize.h"
#include <stdlib.h>

void	remove_empty(token **head)
{
	token	*it;
	token	*next;

	it = *head;
	while (it)
	{
		next = it->next;
		if (it->str && it->str[0] == '\0')
		{
			token_free(token_lst_remove(head, it));
		}
		it = next;
	}
}

void	word_join(token **head)
{
	token	*it;
	char	*new_str;

	it = *head;
	while (it != NULL && it->next != NULL)
	{
		if (it->flags & TOK_RIGHT_JOIN && it->next->flags & TOK_LEFT_JOIN)
		{
			it->flags &= it->next->flags;
			new_str = ft_strjoin(it->str, it->next->str);
			free(it->str);
			token_free(token_lst_remove(head, it->next));
			it->str = new_str;
		}
		else
		{
			it = it->next;
		}
	}
}
