/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:20 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 05:11:22 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

extern char	**g_environ;

// int environ_init(void);
// void environ_cleanup(void);
// int environ_add(char *new_entry);
// void environ_remove(char *entry);
// char *environ_get(char *entry);

// void environ_print(int fd);

// ENV
int			environ_init(void);
char		*environ_get(char *name);
char		*environ_find(char *name);
int			env_var_is_value(char *var_name, char *value);
int			env_is_var_char(char c);

// ENV_MODIFY
int			environ_remove(char *name);
int			environ_add(char *str);
int			environ_set(char *name, char *value);

void		environ_cleanup(void);

#endif // LIB_ENVIRON_ENVIRON_H_
