/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:20 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 05:46:38 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft/libft.h"
#include "lib/parse/src/p_parse.h"
#include "lib/tokenize/tokenize.h"
#include <stdlib.h>

void	cmd_free(t_cmd *c)
{
	if (c->simple_cmd != NULL)
		token_lst_free(&c->simple_cmd);
	if (c->redirect_input != NULL)
		token_lst_free(&c->redirect_input);
	if (c->redirect_output != NULL)
		token_lst_free(&c->redirect_output);
	free(c);
}

void	parse_lst_free(t_cmd **c)
{
	t_cmd	*it;
	t_cmd	*next;

	it = *c;
	while (it)
	{
		next = it->next;
		cmd_free(it);
		it = next;
	}
	*c = NULL;
}
