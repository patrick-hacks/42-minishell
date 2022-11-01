/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:22 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:06:53 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "lib/parse/src/p_parse.h"
#include "lib/tokenize/tokenize.h"
#include <stdlib.h>

void	remove_empty(t_token **head)
{
	t_token	*it;
	t_token	*next;

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

void	word_join(t_token **head)
{
	t_token	*it;
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
