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
  return tok;
}

token *tokenize(char *line) {
  if (!is_range_correct(line)) {
    fprintf(stderr, "Please end what you start\n");
    environ_set("?", "2");
    return NULL;
  }
  token *tokens = NULL;
  int i = 0;
  while (line[i] != '\0') {
    while (line[i] != '\0' && ft_strchr(" \t\n", line[i])) {
      i++;
    }
    if (line[i] == '\0') break;
    token_lst_push_back(&tokens, next_token(line, &i));
  }
  if (getenv("DEBUG")) {
    debug_token_print(tokens);
  }
  if (!is_token_sequence_valid(tokens)) {
    token_lst_free(&tokens);
    fprintf(stderr, "What is that supposed to mean?\n");
    environ_set("?", "2");
  }
  return tokens;
}
