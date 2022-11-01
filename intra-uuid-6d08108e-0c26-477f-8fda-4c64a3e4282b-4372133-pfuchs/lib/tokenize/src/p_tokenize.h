/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_tokenize.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:52 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 05:54:38 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_TOKENIZE_H
# define P_TOKENIZE_H

# include "lib/libft/libft.h"
# include "lib/tokenize/tokenize.h"

int		get_quote(t_token *tok, char *line, int *i);
int		get_special(t_token *tok, char *line, int *i);
int		get_range(t_token *tok, char *line, int *i);
int		get_default(t_token *tok, char *line, int *i);

// token *token_lst_last(token *lst);
void	token_lst_push_back(t_token **lst, t_token *new_token);

// Validity checks in tokenize_error
bool	is_range_correct(char *line);
bool	is_token_sequence_valid(t_token *t);

void	debug_token_print(t_token *tokens);

#endif // LIB_TOKENIZE_SRC_TOKENIZE_H_
