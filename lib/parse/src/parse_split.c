#include <stdio.h>
#include <stdlib.h>

#include "lib/libft/libft.h"
#include "lib/parse/src/parse.h"

static int token_count(token *tok) {
  int i = 0;
  while (tok) {
    tok = tok->next;
    i += 1;
  }
  return i;
}

static void add_tokens(token **tok_list, int i, token *it) {
  tok_list[i] = it;
  it->prev = NULL;
  while (it->next && !(it->next->flags & (TOK_AND | TOK_OR | TOK_OPEN))) {
    it += 1;
  }
  if (it->next) {
    it = it->next;
    it->prev->next = NULL;
    it->prev = NULL;
  }
  add_tokens(tok_list, i + 1, it);
}

token *parse_split(token *tok) {
  token **token_list;

  token_list = ft_calloc_or_die(token_count(tok) / 2 + 1, sizeof(token **));
  add_tokens(token_list, 0, tok);
}
