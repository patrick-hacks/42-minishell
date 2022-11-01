/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:25 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:27:12 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/parse/src/p_parse.h"
#include <stdio.h>
#include <stdlib.h>

t_cmd	*parse(t_token *tok)
{
	t_cmd	*head;
	t_cmd	*it;

	word_join(&tok);
	head = convert_to_command(tok);
	it = head;
	while (it)
	{
		if (extract_redirection(it, tok))
		{
			fprintf(stderr, "no breaking please\n");
			return (0);
		}
		it = it->next;
	}
	if (getenv("DEBUG"))
	{
		debug_cmd_print(head);
	}
	return (head);
}
