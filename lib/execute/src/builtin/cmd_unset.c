/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:43 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:46 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "lib/execute/src/execute.h"

int	cmd_unset(cmd *c, int *fd)
{
	token	*it;

	(void)fd;
	it = c->simple_cmd;
	it = it->next;
	if (!it || it->str[0] == '\0')
		return (0);
	while (it)
	{
		environ_remove(it->str);
		it = it->next;
	}
	return (0);
}
