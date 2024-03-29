/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:37:39 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:14:13 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stddef.h>

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*dest_it;

	dest_it = dest;
	while (*src && n)
	{
		*dest_it = *src;
		dest_it++;
		src++;
		n--;
	}
	if (n)
		*dest_it = '\0';
	return (dest);
}
