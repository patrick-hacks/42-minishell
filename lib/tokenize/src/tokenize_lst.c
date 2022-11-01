/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:47 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 05:57:31 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/tokenize/src/p_tokenize.h"
#include <stdlib.h>

void	token_lst_push_back(t_token **lst, t_token *new_token)
{
	t_token	*it;

	it = *lst;
	new_token->next = NULL;
	if (*lst == NULL)
	{
		*lst = new_token;
		new_token->prev = NULL;
	}
	else
	{
		it = *lst;
		while (it->next != NULL)
			it = it->next;
		it->next = new_token;
		new_token->prev = it;
	}
	it = *lst;
}

t_token	*token_lst_remove(t_token **head, t_token *remove)
{
	if (head && remove == *head)
	{
		*head = remove->next;
		return (remove);
	}
	if (remove->prev)
		remove->prev->next = remove->next;
	if (remove->next)
		remove->next->prev = remove->prev;
	return (remove);
}

void	token_free(t_token *tok)
{
	free(tok->str);
	free(tok);
}

void	token_lst_free(t_token **head)
{
	t_token	*it;
	t_token	*next;

	it = *head;
	while (it)
	{
		next = it->next;
		token_free(it);
		it = next;
	}
	*head = NULL;
}
