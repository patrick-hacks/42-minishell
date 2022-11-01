/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:34 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:14:03 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "lib/execute/src/p_execute.h"
#include <stdio.h>

int	cmd_env(t_cmd *c, int *fd)
{
	int	i;

	i = 0;
	(void)c;
	(void)fd;
	while (g_environ[i])
	{
		dprintf(fd[1], "%s\n", g_environ[i]);
		i++;
	}
	return (0);
}
