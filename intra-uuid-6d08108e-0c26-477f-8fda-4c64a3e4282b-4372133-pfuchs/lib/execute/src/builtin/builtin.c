/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:24 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:13:43 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/execute/src/builtin/builtin.h"
#include "lib/libft/libft.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct s_command_function_pair
{
	char							*name;
	t_builtin_main					function;
}									t_command_function_pair;

int									cmd_cd(t_cmd *c, int *fd);
int									cmd_echo(t_cmd *c, int *fd);
int									cmd_env(t_cmd *c, int *fd);
int									cmd_exit(t_cmd *c, int *fd);
int									cmd_export(t_cmd *c, int *fd);
int									cmd_pwd(t_cmd *c, int *fd);
int									cmd_unset(t_cmd *c, int *fd);

static const t_command_function_pair	g_commands[] = {
{"cd", cmd_cd}, {"echo", cmd_echo}, {"env", cmd_env}, {"exit", cmd_exit},
{"export", cmd_export}, {"pwd", cmd_pwd}, {"unset", cmd_unset}};

t_builtin_main	get_builtin(char *command)
{
	int	i;

	i = 0;
	while (i < (int)(sizeof(g_commands) / sizeof(g_commands[0])))
	{
		if (ft_strncmp(command, g_commands[i].name, 20) == 0)
			return (g_commands[i].function);
		i += 1;
	}
	return (NULL);
}
