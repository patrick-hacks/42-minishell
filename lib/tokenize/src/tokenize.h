#ifndef LIB_TOKENIZE_SRC_TOKENIZE_H_
#define LIB_TOKENIZE_SRC_TOKENIZE_H_

#include "lib/libft/libft.h"
#include "lib/tokenize/tokenize.h"

token *get_quote(char *line, int *i);
token *get_redirect(char *line, int *i);
token *get_pipe(char *line, int *i);
token *get_default(char *line, int *i);

// token *token_lst_last(token *lst);
void token_lst_push_back(token **lst, token *new_token);

// Validity checks in tokenize_error
bool is_quote_correct(char *line);
bool is_redirection_correct(token *t);
bool is_pipe_correct(token *t);

void debug_token_print(token *tokens);

#endif // LIB_TOKENIZE_SRC_TOKENIZE_H_
