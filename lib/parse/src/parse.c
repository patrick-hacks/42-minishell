/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:25 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:35 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/parse/src/parse.h"
#include <stdio.h>
#include <stdlib.h>

cmd	*parse(token *tok)
{
	cmd	*head;
	cmd	*it;

	// remove_empty(&tok);
	word_join(&tok);
	head = convert_to_command(tok);
	it = head;
	while (it)
	{
		if (extract_redirection(it))
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
