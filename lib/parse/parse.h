#ifndef LIB_PARSE_PARSE_H_
#define LIB_PARSE_PARSE_H_

#include "lib/tokenize/tokenize.h"

typedef struct s_cmd {
  token *simple_cmd;
  token *redirect_input;
  token *redirect_output;
  struct s_cmd *next;
  struct s_cmd *prev;
} cmd;

cmd *parse(token *token_lst);
/// @brief Expands the unescaped environment names in the token strings.
/// @param tokens Linked list of tokens
void parse_expand_token(token *tokens);

/// @brief Expands ALL environment variables in the input string. WARNING: this
/// does not check for Quotes. Should be used to expand variable names in
/// heredoc.
/// @param tokens Linked list of tokens
int parse_expand_str(char **str);

/// @brief Frees the whole list of commands. Takes a double pointer to the head of
/// the list and sets it to NULL to prevent use after free.
/// @param head Head of the list
void parse_lst_free(cmd **c);

void debug_cmd_print(cmd *command);

#endif // LIB_PARSE_PARSE_H_
