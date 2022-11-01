/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:43 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:03:19 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/environ/environ.h"
#include "lib/execute/src/p_execute.h"

int	cmd_unset(t_cmd *c, int *fd)
{
	t_token	*it;

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
