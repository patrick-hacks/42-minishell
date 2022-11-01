/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:44 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:12:30 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "lib/libft/libft.h"
#include "lib/tokenize/src/p_tokenize.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct s_token_id
{
	char					token_str[3];
	int						id;
}							t_token_id;

typedef struct s_token_range
{
	char					begin;
	char					end;
	int						id;
}							t_token_range;

// As these are static const they are not concidered "global" by the norm
static const char			*g_meta_chars = "\'\"|<> \n\t";
static const char			*g_meta_join = "|<> \n\t";
static const t_token_id		g_token_ids[] = {
{">>", TOK_APPEND},
{">", TOK_WRITE},
{"<<", TOK_HEREDOC},
{"<", TOK_READ},
{"|", TOK_PIPE},
};
static const t_token_range	g_range[] = {
{'"', '"', TOK_DOUBLE_QUOTED | TOK_WORD},
{'\'', '\'', TOK_SINGLE_QUOTED | TOK_WORD},
};

static int	is_joined(char *line, int i)
{
	if (i < 0 || line[i] == '\0')
		return (false);
	if (ft_strchr(g_meta_join, line[i]))
		return (false);
	return (true);
}

int	get_range(t_token *tok, char *line, int *it)
{
	int		i;
	char	*end;

	i = 0;
	while (i < (int)((sizeof(g_range)) / sizeof(t_token_range)))
	{
		if (g_range[i].begin == line[*it])
		{
			tok->flags = g_range[i].id;
			end = ft_strchr(line + *it + 1, g_range[i].end);
			tok->str = ft_strsub_or_die(line + *it, 1, end - (line + *it) - 1);
			if (is_joined(line + *it, -1))
				tok->flags |= TOK_LEFT_JOIN;
			if (is_joined(line + *it, end - line + 1))
				tok->flags |= TOK_RIGHT_JOIN;
			*it = end - line + 1;
			return (0);
		}
		i += 1;
	}
	return (1);
}

int	get_special(t_token *tok, char *line, int *it)
{
	int	i;

	i = 0;
	while (i < (int)(sizeof(g_token_ids) / sizeof(t_token_id)))
	{
		if (ft_strncmp(g_token_ids[i].token_str, line + *it,
				ft_strlen(g_token_ids[i].token_str)) == 0)
		{
			tok->flags = g_token_ids[i].id;
			*it += ft_strlen(g_token_ids[i].token_str);
			return (0);
		}
		i += 1;
	}
	return (1);
}

int	get_default(t_token *tok, char *line, int *it)
{
	int	start;

	tok->flags |= TOK_WORD;
	start = *it;
	while (!ft_strchr(g_meta_chars, line[*it]))
		*it += 1;
	tok->str = ft_strsub_or_die(line, start, *it - start);
	if (is_joined(line, start - 1))
		tok->flags |= TOK_LEFT_JOIN;
	if (is_joined(line, *it))
		tok->flags |= TOK_RIGHT_JOIN;
	return (0);
}
