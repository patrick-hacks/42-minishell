/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:39:17 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/03 16:43:33 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"

#include <stdlib.h>
#include <unistd.h>

#include "lib/libft/libft.h"

extern char	**environ;
char		**g_environ;

void	environ_cleanup(void)
{
	char	**it;

	it = g_environ;
	while (*it)
	{
		free(*it);
		*it = NULL;
		it++;
	}
	free(g_environ);
}

int	environ_init(void)
{
	char	**it;

	it = environ;
	g_environ = malloc(sizeof(char *));
	if (!g_environ)
		return (1);
	*g_environ = NULL;
	while (*it)
	{
		if (environ_add(*it))
		{
			return (1);
		}
		it++;
	}
	return (0);
}

void	environ_print(void)
{
	char	**it;

	it = environ;
	while (*it)
	{
		write(1, *it, ft_strlen(*it));
		write(1, "\n", 1);
		it++;
	}
}
