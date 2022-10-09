/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_pointer_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:01:25 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/03 10:03:48 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

void	ft_free_pointer_array(void	**array)
{
	void	**it;

	it = array;
	while (*it)
	{
		free(*it);
		it++;
	}
	free(array);
}
