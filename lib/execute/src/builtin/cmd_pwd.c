/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:41 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:03:06 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/execute/src/p_execute.h"
#include <limits.h> // PATH_MAX
#include <stdio.h>  // printf
#include <unistd.h> // getcwd

int	cmd_pwd(t_cmd *c, int *fd)
{
	char	cwd[PATH_MAX];

	(void)c;
	(void)fd;
	cwd[0] = '\0';
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		fprintf(stderr, "could not determine directory\n");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
