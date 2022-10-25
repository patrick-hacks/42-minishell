/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:34 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:49 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "lib/execute/src/execute.h"
#include <stdio.h>

int	cmd_env(cmd *c, int *fd)
{
	(void)c;
	(void)fd;
	int i = 0;
	while (g_environ[i])
	{
		dprintf(fd[1], "%s\n", g_environ[i]);
		i++;
	}
	return (0);
}
