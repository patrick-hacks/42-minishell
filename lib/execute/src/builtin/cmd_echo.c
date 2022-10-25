/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:32 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:50 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/execute/src/execute.h"
#include "lib/libft/libft.h"
#include <stdbool.h>
#include <stdio.h>

int	cmd_echo(cmd *c, int *fd)
{
	token	*it;
	int		new_line;

	// fprintf(stderr, "in: %d, out: %d\n", fd[0], fd[1]);
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
	// close_or_die(fd[0]);
	// close_or_die(fd[1]);
}
