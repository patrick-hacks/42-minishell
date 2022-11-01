/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 08:47:26 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/11 09:58:12 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_memset

#include <stdlib.h> // malloc
#include <stddef.h> // NULL size_t

// Allocates memory for "num" items with "size", initialises to 0
void	*ft_calloc_or_die(size_t num, size_t size)
{
	char	*memory;

	if (size && num > ((size_t)-1) / size)
		exit(-1);
	memory = (char *)malloc(num * size);
	if (!memory)
		exit(-1);
	ft_memset(memory, 0, num * size);
	return (memory);
}
