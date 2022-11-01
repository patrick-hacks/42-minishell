/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:55 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 05:49:54 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <stdbool.h>
# include <stdint.h>

# define TOK_WORD 0b1

// Ranges
# define TOK_SINGLE_QUOTED 0b10
# define TOK_DOUBLE_QUOTED 0b100
# define TOK_BRACKET 0b1000

// Joins
# define TOK_LEFT_JOIN 0b10000
# define TOK_RIGHT_JOIN 0b100000

// Redirect
# define TOK_READ 0b1000000
# define TOK_WRITE 0b10000000
# define TOK_APPEND 0b100000000
# define TOK_HEREDOC 0b1000000000
# define TOK_REDIRECT 0b1111000000

// Meta
# define TOK_PIPE 0b10000000000
# define TOK_AND 0b100000000000
# define TOK_OR 0b1000000000000
# define TOK_CONNECTOR 0b1110000000000

/// @brief Token node of a double linked list holding the string and flags set
/// as bits.
typedef struct s_token
{
	uint16_t		flags;
	char			*str;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

/// @brief Splits the input into tokens which hold a string and bits set on
/// flags integer. Defines for Flags start with TOK_. Has to be freed with a
/// call to token_lst_free.
/// @param line Input string
/// @return Double linked list of tokens
t_token				*tokenize(char *line);

/// @brief Frees a single token
/// @param tok Token to be freed
void				token_free(t_token *tok);

/// @brief Adds a single token to the end of the list.
/// @param head
/// @param new_token
void				token_lst_push_back(t_token **head, t_token *new_token);

/// @brief Removes a specific token from the list of tokens keeping the chain
/// intact. The token does NOT get freed and is returned.
/// @param head Head of the token list
/// @param remove Token to be removed
/// @return Token that got removed
t_token				*token_lst_remove(t_token **head, t_token *remove);

/// @brief Frees the whole list of tokens. Takes a double pointer to the head of
/// the list and sets it to NULL to prevent use after free.
/// @param head Head of the list
void				token_lst_free(t_token **head);

#endif // LIB_TOKENIZE_TOKENIZE_H_
