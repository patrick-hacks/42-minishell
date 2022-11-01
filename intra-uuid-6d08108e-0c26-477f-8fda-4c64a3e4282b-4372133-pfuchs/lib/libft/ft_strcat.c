/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 23:22:49 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/03 13:04:40 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strlen

#include <stddef.h> // NULL size_t

char	*ft_strcat(char *dest, const char *src)
{
	char	*dest_it;

	dest_it = dest;
	while (*dest_it)
		dest_it++;
	while (*src)
	{
		*dest_it = *src;
		dest_it++;
		src++;
	}
	*dest_it = '\0';
	return (dest);
}
