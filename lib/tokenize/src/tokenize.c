#include "lib/tokenize/src/tokenize.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/environ/environ.h"

static token *next_token(char *line, int *i) {
  token *tok = ft_calloc_or_die(1, sizeof(token));
  if (get_range(tok, line, i) == 0) return tok;
  if (get_special(tok, line, i) == 0) return tok;
  get_default(tok, line, i);
  printf("made token %d\n", *i);
  return tok;
}

token *tokenize(char *line) {
  if (!is_range_correct(line)) {
    fprintf(stderr, "No breaking please :(\n");
    return NULL;
  }
  token *tokens = NULL;
  const char *ifs = environ_get("IFS");
  int i = 0;
  while (line[i] != '\0') {
    printf(".\n");
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
