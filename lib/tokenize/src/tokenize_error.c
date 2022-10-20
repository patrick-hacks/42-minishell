#include <stdbool.h>
#include <stdlib.h>

#include "lib/tokenize/src/tokenize.h"

bool is_range_correct(char *line) {
  if (!line) return false;
  while (*line) {
    if (*line == '\'') line = ft_strchr(line + 1, '\'');
    if (*line == '\"') line = ft_strchr(line + 1, '\"');
    if (*line == ')') return false;
    if (*line == '(') line = ft_strchr(line + 1, ')');
    line++;
  }
  return true;
}

static bool is_first_valid(token *t) {
  if (t->flags & TOK_WORD) return true;
  if (t->flags & TOK_REDIRECT) return true;
  if (t->flags & TOK_OPEN) return true;
  return false;
}

static bool is_center_valid(token *t) {
  if (t->prev->flags & TOK_REDIRECT) {
    if (t->flags & TOK_WORD) return true;
    return false;
  }
  if (t->prev->flags & TOK_OPEN) {
    return is_first_valid(t);
  }
  if (t->prev->flags & TOK_CLOSE) {
    if (t->flags & TOK_CONNECTOR) return true;
  }
  if (t->prev->flags & TOK_CONNECTOR) {
    if (t->flags & TOK_OPEN) return true;
    if (t->flags & TOK_WORD) return true;
    return false;
  }
  return true;
}

static bool is_last_valid(token *t) {
  if (t->flags & TOK_WORD) return true;
  if (t->flags & TOK_CLOSE) return true;
  return false;
}

#include <stdio.h>

bool is_token_sequence_valid(token *t) {
  if (!is_first_valid(t)) return false;
  while (t->next) {
    t = t->next;
    if (!is_center_valid(t)) return false;
  }
  if (!is_last_valid(t)) return false;
  return true;
}
