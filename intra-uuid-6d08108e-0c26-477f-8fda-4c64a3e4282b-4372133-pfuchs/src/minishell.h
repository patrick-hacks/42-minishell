/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:17:06 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:07:18 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/environ/environ.h"
# include "lib/parse/parse.h"
# include "lib/tokenize/tokenize.h"

int		minishell(void);

int		heredoc_replace(t_cmd *c);
void	heredoc_cleanup(t_cmd *c);

# define SIG_READLINE 0
# define SIG_SUBSHELL 1
# define SIG_EXE 2
# define SIG_HEREDOC 3
# define SIG_HEREDOC_CHILD 4

void	set_signal(int mode);
void	set_termios(int mode);

#endif // SRC_MINISHELL_H_
