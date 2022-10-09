#include "lib/tokenize/src/tokenize.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "lib/environ/environ.h"

static token *next_token(char *line, int *i) {
  switch (line[*i]) {
    case '\"':
    case '\'':
      return get_quote(line, i);
    case '<':
    case '>':
      return get_redirect(line, i);
    case '|':
      return get_pipe(line, i);
    default:
      return get_default(line, i);
  }
}

token *tokenize(char *line) {
  if (!is_quote_correct(line)) {
    fprintf(stderr, "No breaking please :(\n");
    return NULL;
  }
  token *tokens = NULL;
  const char *ifs = environ_get("IFS");
  int i = 0;
  while (line[i] != '\0') {
    while (line[i] != '\0' && ft_strchr(ifs, line[i])) {
      i++;
    }
    if (line[i] == '\0') break;
    token_lst_push_back(&tokens, next_token(line, &i));
  }
  if (getenv("DEBUG")) {
    debug_token_print(tokens);
  }
  if (!is_redirection_correct(tokens) || !is_pipe_correct(tokens)) {
    token_lst_free(&tokens);
    fprintf(stderr, "no breaking please :(\n");
  }
  return (tokens);
}
