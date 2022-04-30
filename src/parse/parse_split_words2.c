/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_words2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 10:00:39 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/30 20:17:54 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	g_meta_seperators[] = "|&<>()";
static const char	g_meta_double_seperators[] = "|&<>";

const char	*next_split_location(const char *str, const char *delims)
{
	while (*str && ft_strchr(delims, *str))
		str++;
	return (str);
}

static int	get_quote(char c, char quote)
{
	//printf("testing char %c on quote: %c\n", c, quote);
	if (c == '\'' && quote != '\"')
	{
		if (quote == '\'')
			return (0);
		else
			return ('\'');
	}
	if (c == '\"' && quote != '\'')
	{
		if (quote == '\"')
			return (0);
		else
			return ('\"');
	}
	return (quote);
}

int	split_length2(const char *str, const char *delims, int i)
{
	int		delim_start;
	char	*is_meta;
	char	*is_delim;

	delim_start = 0;
	is_meta = ft_strchr(g_meta_seperators, str[i]);
	is_delim = ft_strchr(delims, str[i]);
	if (is_delim)
		return (i);
	if (is_meta)
	{
		if (i == 0)
		{
			if (str[1] && ft_strchr(g_meta_double_seperators, str[1]))
				return (2);
			return (1);
		}
		return (i);
	}
	return (-1);
}

int	split_length(const char *str, const char *delims)
{
	int		i;
	int		length;
	char	quote;

	i = 0;
	quote = 0;
	//printf("getting length for %s\n", str);
	while (str[i])
	{
		quote = get_quote(str[i], quote);
		//printf("quote: %c", quote);
		if (!quote)
		{
			length = split_length2(str, delims, i);
			if (length != -1)
			{
				//printf("found length: %d\n", length);
				return (length);
			}
		}
		i++;
	}
	//printf("end of string %d\n", i);
	return (i);
}

int	count_splits(const char *str, const char *delims)
{
	int		splits;

	splits = 0;
	while (1)
	{
		while (*str && ft_strchr(delims, *str))
			str++;
		if (*str == '\0')
		{
			//printf("counted %d splits\n", splits);
			return (splits);
		}
		str += split_length(str, delims);
		splits++;
	}
}
