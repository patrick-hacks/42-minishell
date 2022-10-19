#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "lib/environ/environ.h"
#include "lib/libft/libft.h"
#include "lib/tokenize/tokenize.h"

static int replace(char **str_pointer, int begin, int end) {
  char *str = *str_pointer;
  char tmp = str[end];
  str[end] = '\0';
  char *replacement = environ_get(str + begin + 1);
  if (!replacement) replacement = "";
  str[end] = tmp;
  int new_length = begin + ft_strlen(replacement) + (ft_strlen(str) - end);
  char *new_str = ft_calloc_or_die(1, new_length + 10);
  ft_strncpy(new_str, str, begin);
  ft_strcat(new_str, replacement);
  ft_strcat(new_str, str + end);
  free(str);
  *str_pointer = new_str;
  return begin + ft_strlen(replacement);
}

static void expand_env(token *token) {
  int i = 0;
  while (token->str[i]) {
    if (token->str[i] == '$') {
      int begin = i;
      while (token->str[i] && token->str[i] != ' ') i++;
      if (i - begin > 1 || token->flags | TOK_RIGHT_JOIN) {
        if (token->str[1] != ' ' && token->str[1])
          i = replace(&token->str, begin, i) - 1;
      }
    }
    i += 1;
  }
}

void parse_expand_token(token *tokens) {
  token *it = tokens;
  while (it != NULL) {
    if ((it->flags & TOK_WORD) && !(it->flags & TOK_SINGLE_QUOTED)) {
      expand_env(it);
    }
    it = it->next;
  }
}

int parse_expand_str(char *str, int max_len) {
  int i = 0;
  while (str[i]) {
    if (str[i] == '$') {
      int begin = i;
      while (str[i] && str[i] != ' ') i++;
      if (i >= max_len) return 1;
      i = replace(&str, begin, i) - 1;
    }
    i += 1;
  }
  return 0;
}
