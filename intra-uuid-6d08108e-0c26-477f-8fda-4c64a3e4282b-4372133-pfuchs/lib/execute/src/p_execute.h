/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_execute.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:15:58 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:13:21 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_EXECUTE_H
# define P_EXECUTE_H

// #include "lib/tokenize/include/tokenize.h"
# include "lib/execute/execute.h"
# include "lib/parse/parse.h"

// typedef struct s_t_cmd {
//   token *simple_t_cmd;
//   token *redirect_input;
//   token *redirect_output;
//   struct s_t_cmd *next;
//   struct s_t_cmd *prev;
// } t_cmd;

int		set_command_path(char **t_cmd);
char	*find_command(char *t_cmd);
void	child_redirect(t_cmd *c, int *fd);
void	child_redirect_builtin(t_cmd *c, int *fd);
void	child_run(t_cmd *c, int *fd);
int		child_run_builtin(t_cmd *c, int *fd);
int		command_count(t_cmd *c);
void	set_pipe(t_cmd *c, int fd[3]);
int		child_fork(t_cmd *c, int *fd);
int		handle_wait_status(int *pids);

char	*find_command(char *t_cmd);
void	pipe_or_die(int *fd);
int		fork_or_die(void);
void	close_or_die(int fd);
void	execve_or_die(char *t_cmd, char **argv, char **env);
int		get_argc(t_cmd *c);
char	**get_argv(t_cmd *c);
int		execute_t_cmd(t_cmd *c);
int		execute_fork(t_cmd *c);

#endif // LIB_EXECUTE_SRC_EXECUTE_H_
