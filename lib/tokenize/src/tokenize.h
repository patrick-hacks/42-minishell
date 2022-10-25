/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:52 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:18:44 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_TOKENIZE_SRC_TOKENIZE_H_
# define LIB_TOKENIZE_SRC_TOKENIZE_H_

# include "lib/libft/libft.h"
# include "lib/tokenize/tokenize.h"

int		get_quote(token *tok, char *line, int *i);
int		get_special(token *tok, char *line, int *i);
int		get_range(token *tok, char *line, int *i);
int		get_default(token *tok, char *line, int *i);

// token *token_lst_last(token *lst);
void	token_lst_push_back(token **lst, token *new_token);

// Validity checks in tokenize_error
bool	is_range_correct(char *line);
bool	is_token_sequence_valid(token *t);

void	debug_token_print(token *tokens);

#endif // LIB_TOKENIZE_SRC_TOKENIZE_H_
