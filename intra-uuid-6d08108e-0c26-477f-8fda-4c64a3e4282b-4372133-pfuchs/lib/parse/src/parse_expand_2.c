/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:18 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:31:16 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "lib/libft/libft.h"
#include "lib/tokenize/tokenize.h"
#include <dirent.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

void	expand_star(t_token *token);
void	expand_env(t_token *token);
int		replace(char **str_pointer, int begin, int end);
int		is_same_wildcard(char *wildcard_str, char *str);
void	remove_token(t_token *token_list);
void	insert_token(t_token *token_list, char *str);

void	parse_expand_token(t_token *tokens)
{
	t_token	*it;

	it = tokens;
	while (it != NULL)
	{
		if ((it->flags & TOK_WORD) && !(it->flags & TOK_SINGLE_QUOTED))
		{
			expand_env(it);
			expand_star(it);
		}
		it = it->next;
	}
}

int	parse_expand_str(char **str)
{
	int	i;
	int	begin;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			begin = i;
			while ((*str)[i] && ft_strchr(" \t\n\"\'", (*str)[i]) == NULL)
				i++;
			i = replace(str, begin, i) - 1;
		}
		i += 1;
	}
	return (0);
}

void	expand_star(t_token *token)
{
	DIR				*d;
	bool			expanded;
	struct dirent	*dir;

	if (ft_strchr(token->str, '*') == NULL)
		return ;
	if (environ_get("PWD") == NULL)
		return ;
	d = opendir(environ_get("PWD"));
	if (!d)
		return ;
	expanded = false;
	dir = readdir(d);
	while (dir)
	{
		if (dir->d_name[0] != '.' && is_same_wildcard(token->str, dir->d_name))
		{
			insert_token(token, dir->d_name);
			expanded = true;
		}
		dir = readdir(d);
	}
	if (expanded)
		remove_token(token);
}
