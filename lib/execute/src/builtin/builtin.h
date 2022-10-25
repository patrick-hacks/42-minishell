/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:26 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:52 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_EXECUTE_SRC_BUILTIN_BUILTIN_H_
# define LIB_EXECUTE_SRC_BUILTIN_BUILTIN_H_

# include "lib/execute/src/execute.h"

typedef int		(*builtin_main)(cmd *c, int *fd);

builtin_main	get_builtin(char *command);

#endif // LIB_EXECUTE_SRC_BUILTIN_BUILTIN_H_
