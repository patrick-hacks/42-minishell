/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:24:01 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/03 13:02:44 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strlen ft_memcpy

char	*ft_strcpy(char *dest, const char *src)
{
	char	*dest_it;

	dest_it = dest;
	while (*src)
	{
		*dest_it = *src;
		dest_it++;
		src++;
	}
	*dest_it = '\0';
	return (dest);
}
