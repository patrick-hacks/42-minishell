/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:58 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:42 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_EXECUTE_SRC_EXECUTE_H_
# define LIB_EXECUTE_SRC_EXECUTE_H_

// #include "lib/tokenize/include/tokenize.h"
# include "lib/execute/execute.h"
# include "lib/parse/parse.h"

// typedef struct s_cmd {
//   token *simple_cmd;
//   token *redirect_input;
//   token *redirect_output;
//   struct s_cmd *next;
//   struct s_cmd *prev;
// } cmd;

int		set_command_path(char **cmd);
char	*find_command(char *cmd);
void	child_redirect(cmd *c, int *fd);
void	child_redirect_builtin(cmd *c, int *fd);
void	child_run(cmd *c, int *fd);
int		child_run_builtin(cmd *c, int *fd);

char	*find_command(char *cmd);
void	pipe_or_die(int *fd);
int		fork_or_die(void);
void	close_or_die(int fd);
void	execve_or_die(char *cmd, char **argv, char **env);
int		get_argc(cmd *c);
char	**get_argv(cmd *c);

#endif // LIB_EXECUTE_SRC_EXECUTE_H_
