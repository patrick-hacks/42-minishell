#ifndef LIB_TOKENIZE_TOKENIZE_H_
#define LIB_TOKENIZE_TOKENIZE_H_

#include <stdbool.h>
#include <stdint.h>

#define TOK_WORD 1 << 0

// Ranges
#define TOK_SINGLE_QUOTED (1 << 1)
#define TOK_DOUBLE_QUOTED (1 << 2)

// Joins
#define TOK_LEFT_JOIN (1 << 4)
#define TOK_RIGHT_JOIN (1 << 5)

// Redirect
#define TOK_READ (1 << 6)
#define TOK_WRITE (1 << 7)
#define TOK_APPEND (1 << 8)
#define TOK_HEREDOC (1 << 9)
#define TOK_REDIRECT (TOK_READ | TOK_WRITE | TOK_APPEND | TOK_HEREDOC)

// Meta
#define TOK_PIPE (1 << 10)
#define TOK_AND (1 << 11)
#define TOK_OR (1 << 12)
#define TOK_OPEN (1 << 13)
#define TOK_CLOSE (1 << 14)

#define TOK_CONNECTOR (TOK_PIPE | TOK_AND | TOK_OR)

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

token **tokenize_split(token *tok);

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
