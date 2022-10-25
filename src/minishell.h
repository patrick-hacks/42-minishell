/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:17:06 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:24 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRC_MINISHELL_H_
# define SRC_MINISHELL_H_

# include "lib/environ/environ.h"
# include "lib/parse/parse.h"
# include "lib/tokenize/tokenize.h"

int		minishell(void);

int		heredoc_replace(cmd *c);
void	heredoc_cleanup(cmd *c);

# define SIG_READLINE 0
# define SIG_SUBSHELL 1
# define SIG_EXE 2
# define SIG_HEREDOC 3
# define SIG_HEREDOC_CHILD 4

void	set_signal(int mode);
void	set_termios(int mode);

#endif // SRC_MINISHELL_H_
