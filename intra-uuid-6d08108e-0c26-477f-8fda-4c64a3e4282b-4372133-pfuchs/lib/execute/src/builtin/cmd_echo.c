/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:32 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:02:12 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/execute/src/p_execute.h"
#include "lib/libft/libft.h"
#include <stdbool.h>
#include <stdio.h>

int	cmd_echo(t_cmd *c, int *fd)
{
	t_token	*it;
	int		new_line;

	it = c->simple_cmd->next;
	new_line = true;
	while (it && ft_strncmp(it->str, "-n", 3) == 0)
	{
		it = it->next;
		new_line = false;
	}
	while (it)
	{
		dprintf(fd[1], "%s", it->str);
		it = it->next;
		if (it)
			dprintf(fd[1], " ");
	}
	if (new_line)
		dprintf(fd[1], "\n");
	return (0);
}
