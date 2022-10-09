#ifndef LIB_TOKENIZE_TOKENIZE_H_
#define LIB_TOKENIZE_TOKENIZE_H_

#include <stdbool.h>
#include <stdint.h>

#define TOK_WORD 0b1 << 0

#define TOK_SINGLE_QUOTED 0b1 << 1
#define TOK_DOUBLE_QUOTED 0b1 << 2
#define TOK_LEFT_JOIN 0b1 << 3
#define TOK_RIGHT_JOIN 0b1 << 4

#define TOK_REDIRECT 0b1 << 5
#define TOK_READ 0b1 << 6
#define TOK_WRITE 0b1 << 7
#define TOK_APPEND 0b1 << 8
#define TOK_HEREDOC 0b1 << 9

#define TOK_PIPE 0b1 << 10

/// @brief Token node of a double linked list holding the string and flags set
/// as bits.
typedef struct s_token {
  uint16_t flags;
  char *str;
  struct s_token *next;
  struct s_token *prev;
} token;

/// @brief Splits the input into tokens which hold a string and bits set on
/// flags integer. Defines for Flags start with TOK_. Has to be freed with a
/// call to token_lst_free.
/// @param line Input string
/// @return Double linked list of tokens
token *tokenize(char *line);

/// @brief Frees a single token
/// @param tok Token to be freed
void token_free(token *tok);

/// @brief Adds a single token to the end of the list.
/// @param head
/// @param new_token
void token_lst_push_back(token **head, token *new_token);

/// @brief Removes a specific token from the list of tokens keeping the chain
/// intact. The token does NOT get freed and is returned.
/// @param head Head of the token list
/// @param remove Token to be removed
/// @return Token that got removed
token *token_lst_remove(token **head, token *remove);

/// @brief Frees the whole list of tokens. Takes a double pointer to the head of
/// the list and sets it to NULL to prevent use after free.
/// @param head Head of the list
void token_lst_free(token **head);

#endif // LIB_TOKENIZE_TOKENIZE_H_
