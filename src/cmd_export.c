/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 02:37:59 by pfuchs            #+#    #+#             */
/*   Updated: 2022/04/29 08:24:55 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_export.h"

#include "environ.h"

int	cmd_export(char *str, int in_fd, int out_fd)
{
	(void) in_fd;
	(void) out_fd;
	environ_add(str);
	return (0);
}