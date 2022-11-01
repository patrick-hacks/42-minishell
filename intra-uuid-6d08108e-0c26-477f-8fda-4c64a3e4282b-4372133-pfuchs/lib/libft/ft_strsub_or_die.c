/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_or_die.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:59:41 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:14:35 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strndup

#include <stdlib.h>

char	*ft_strsub_or_die(char const *str, unsigned int start, size_t n)
{
	char	*new_str;

	new_str = ft_strsub(str, start, n);
	if (!new_str)
		exit(-1);
	return (new_str);
}
