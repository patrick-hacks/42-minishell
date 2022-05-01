/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:46:30 by pfuchs            #+#    #+#             */
/*   Updated: 2022/05/01 07:57:21 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

# include "cmd_export.h"

typedef int	(*t_cmd_function)(char *, int, int);

t_cmd_function	get_function(char *command);

#endif // CMDS_H
