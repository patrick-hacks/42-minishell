#include <stdio.h>
#include <stdlib.h>

#include "lib/libft/libft.h"
#include "lib/tokenize/src/tokenize.h"

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
  if (!it) return;
  it = it->next;
  while (it && !(it->flags & (TOK_AND | TOK_OR | TOK_OPEN | TOK_CLOSE))) {
    it=it->next;
  }
  if (it) {
    it->prev->next = NULL;
    it->prev = NULL;
  }
  add_tokens(tok_list, i + 1, it);
}

token **tokenize_split(token *tok) {
  token **token_list;

  token_list = ft_calloc_or_die(token_count(tok) + 10, sizeof(token **));
  add_tokens(token_list, 0, tok);
  if (getenv("DEBUG")) {
    debug_tokenlist_print(token_list);
  }
  return token_list;
}
