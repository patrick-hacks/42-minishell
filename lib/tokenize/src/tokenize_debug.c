/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:35 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 05:54:54 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/tokenize/src/p_tokenize.h"
#include <stdio.h>

static void	debug_token_flag(t_token *tokens, int flag)
{
	if (tokens->flags & flag)
		printf(" \033[1;41m    \033[0m |");
	else
		printf("      |");
}

void	debug_token_print(t_token *tokens)
{
	int	i;

	printf("\033[1;43m");
	printf(
		"       String       || Word | Sing | Doub | Brac | Left | Righ | "
		"Read | Writ | Appe | Here | Pipe |  AND |  OR  |");
	printf("\033[0m\n");
	while (tokens)
	{
		if (tokens->flags & TOK_WORD)
			printf("%-20s||", tokens->str);
		else
			printf("%-20c||", ' ');
		i = 1;
		while (i <= TOK_OR)
		{
			debug_token_flag(tokens, i);
			i <<= 1;
		}
		tokens = tokens->next;
		printf("\n");
	}
}
