/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:16:04 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/03 16:38:08 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>
#include <stdio.h>

static int	get_combined_length(char **split, char *seperator)
{
	int	length;

	length = 0;
	while (*split)
	{
		length += ft_strlen(*split);
		if (seperator)
			length += ft_strlen(seperator);
		split++;
	}
	return (length);
}

char	*ft_strjoin_array(char **split, char *seperator)
{
	char	*str;
	char	*str_it;
	int		length;

	str = malloc(get_combined_length(split, seperator) + 1);
	if (!str)
		return (NULL);
	str_it = str;
	while (*split)
	{
		length = ft_strlen(*split);
		ft_memcpy(str_it, *split, length);
		str_it += length;
		if (seperator)
		{
			length = ft_strlen(seperator);
			ft_memcpy(str_it, seperator, length);
			str_it += length;
		}
		split += 1;
	}
	return (str);
}
