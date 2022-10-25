/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:41 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:47 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/execute/src/execute.h"
#include <limits.h> // PATH_MAX
#include <stdio.h>  // printf
#include <unistd.h> // getcwd

int	cmd_pwd(cmd *c, int *fd)
{
	(void)c;
	(void)fd;
	char cwd[PATH_MAX];

	cwd[0] = '\0';
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		fprintf(stderr, "could not determine directory\n");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
