#include <stdlib.h>

#include "lib/libft/libft.h"
#include "lib/parse/src/parse.h"
#include "lib/tokenize/tokenize.h"

void cmd_free(cmd *c) {
  if (c->simple_cmd != NULL) token_lst_free(&c->simple_cmd);
  if (c->redirect_input != NULL) token_lst_free(&c->redirect_input);
  if (c->redirect_output != NULL) token_lst_free(&c->redirect_output);
  free(c);
}

void parse_lst_free(cmd **c) {
  cmd *it = *c;
  while (it) {
    cmd *next = it->next;
    cmd_free(it);
    it = next;
  }
  *c = NULL;
}
