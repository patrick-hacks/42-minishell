#include <stdbool.h>
#include <stdlib.h>

#include "lib/tokenize/src/tokenize.h"

bool is_quote_correct(char *line) {
  while (*line) {
    if (*line == '\'') line = ft_strchr(line + 1, '\'');
    if (*line == '\"') line = ft_strchr(line + 1, '\"');
    if (!line) return false;
    line++;
  }
  return true;
}

bool is_redirection_correct(token *t) {
  while (t) {
    if (t->flags & TOK_REDIRECT) {
      if (!t->next || !(t->next->flags & TOK_WORD)) return false;
    }
    t = t->next;
  }
  return true;
}

bool is_pipe_correct(token *t) {
  while (t) {
    if (t->flags & TOK_PIPE) {
      if (!t->prev) return false;
      if (!t->next) return false;
    }
    t = t->next;
  }
  return true;
}
