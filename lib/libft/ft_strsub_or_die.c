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

#include <stdlib.h>

char	*ft_strsub_or_die(char const *str, unsigned int start, size_t n)
{
	char *new_str = ft_strsub(str, start, n);
	if (!new_str)
		exit(-1);
	return new_str;
}
