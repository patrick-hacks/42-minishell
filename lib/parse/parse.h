/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:30 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:12:51 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "lib/tokenize/tokenize.h"

typedef struct s_cmd
{
	t_token			*simple_cmd;
	t_token			*redirect_input;
	t_token			*redirect_output;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

t_cmd				*parse(t_token *token_lst);
/// @brief Expands the unescaped environment names in the token strings.
/// @param tokens Linked list of tokens
void				parse_expand_token(t_token *tokens);

/// @brief Expands ALL environment variables in the input string. WARNING: this
/// does not check for Quotes. Should be used to expand variable names in
/// heredoc.
/// @param tokens Linked list of tokens
int					parse_expand_str(char **str);

/// @brief Frees the whole list of commands.
/// Takes a double pointer to the head of
/// the list and sets it to NULL to prevent use after free.
/// @param head Head of the list
void				parse_lst_free(t_cmd **c);

void				debug_cmd_print(t_cmd *command);

#endif // LIB_PARSE_PARSE_H_
