/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:59:41 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/03 12:41:51 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strndup

#include <stddef.h> // NULL size_t
#include <stdlib.h> // malloc

// returns the length of "str" or n if str is longer;
static size_t	strnlen(const char *str, size_t n)
{
	const char	*ptr;

	ptr = str;
	while (*ptr && n)
	{
		ptr++;
		n--;
	}
	return (ptr - str);
}

// same as strndub but with offset "start"
char	*ft_strsub(char const *str, unsigned int start, size_t n)
{
	size_t	length;
	char	*new_str;

	length = ft_strlen(str);
	if (length < start)
		start = length;
	str += start;
	n = strnlen(str, n);
	new_str = (char *)malloc(n + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str, n);
	new_str[n] = '\0';
	return (new_str);
}
