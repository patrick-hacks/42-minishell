/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:20 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:37 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "lib/parse/src/parse.h"
#include "lib/tokenize/tokenize.h"
#include <stdlib.h>

void	cmd_free(cmd *c)
{
	if (c->simple_cmd != NULL)
		token_lst_free(&c->simple_cmd);
	if (c->redirect_input != NULL)
		token_lst_free(&c->redirect_input);
	if (c->redirect_output != NULL)
		token_lst_free(&c->redirect_output);
	free(c);
}

void	parse_lst_free(cmd **c)
{
	cmd	*it;
	cmd	*next;

	it = *c;
	while (it)
	{
		next = it->next;
		cmd_free(it);
		it = next;
	}
	*c = NULL;
}
