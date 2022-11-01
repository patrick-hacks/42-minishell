/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:18 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:31:12 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "lib/libft/libft.h"
#include "lib/tokenize/tokenize.h"
#include <dirent.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

int	replace(char **str_pointer, int begin, int end)
{
	char	*str;
	char	tmp;
	char	*replacement;
	int		new_length;
	char	*new_str;

	str = *str_pointer;
	tmp = str[end];
	str[end] = '\0';
	replacement = environ_get(str + begin + 1);
	if (!replacement)
		replacement = "";
	str[end] = tmp;
	new_length = begin + ft_strlen(replacement) + (ft_strlen(str) - end);
	new_str = ft_calloc_or_die(1, new_length + 10);
	ft_strncpy(new_str, str, begin);
	ft_strcat(new_str, replacement);
	ft_strcat(new_str, str + end);
	free(str);
	*str_pointer = new_str;
	return (begin + ft_strlen(replacement));
}

void	expand_env(t_token *token)
{
	int	i;
	int	begin;

	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$')
		{
			begin = i;
			while (token->str[i] && token->str[i] != ' ')
				i++;
			if (token->flags & TOK_RIGHT_JOIN
				&& !(token->flags & TOK_DOUBLE_QUOTED))
			{
				i = replace(&token->str, begin, i) - 1;
			}
			else
			{
				if (i - begin > 1 && (token->str[1] != ' ' || token->str[1]))
					i = replace(&token->str, begin, i) - 1;
			}
		}
		i += 1;
	}
}

int	is_same_wildcard(char *wildcard_str, char *str)
{
	if (!*str && !*wildcard_str)
		return (1);
	if (*str == *wildcard_str)
	{
		if (is_same_wildcard(wildcard_str + 1, str + 1))
			return (1);
	}
	if (*wildcard_str == '*')
	{
		if (is_same_wildcard(wildcard_str + 1, str))
			return (1);
		if (*str && is_same_wildcard(wildcard_str, str + 1))
			return (1);
	}
	return (0);
}

void	remove_token(t_token *token_list)
{
	t_token	*remove;

	remove = token_list->next;
	free(token_list->str);
	token_list->str = token_list->next->str;
	token_list->next = token_list->next->next;
	if (token_list->next->next)
	{
		token_list->next->next->prev = token_list;
	}
	free(remove);
}

void	insert_token(t_token *token_list, char *str)
{
	t_token	*new_token;

	new_token = ft_calloc_or_die(1, (sizeof(t_token)));
	new_token->str = ft_strdup(str);
	new_token->next = token_list->next;
	if (new_token->next)
		new_token->next->prev = new_token;
	new_token->prev = token_list;
	token_list->next = new_token;
}
