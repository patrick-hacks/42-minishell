/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:26 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:00:46 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "lib/execute/src/p_execute.h"

typedef int		(*t_builtin_main)(t_cmd *c, int *fd);

t_builtin_main	get_builtin(char *command);

#endif // LIB_EXECUTE_SRC_BUILTIN_BUILTIN_H_
