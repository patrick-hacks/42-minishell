/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 00:17:20 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/01 14:02:31 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

#include <stdio.h>

#include "libft.h"

// enum e_error {
// 	e_alloc_fail = 1,
// 	e_parse = 2
// };

static const char	*g_error_msg[] = {
	"error: important allocation failed\n",
	"error: parsing failed",
};

int	error(enum e_error error)
{
	printf("%s\n", g_error_msg[error]);
	return (error);
	//exit(error);
}