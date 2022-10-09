#include <stdlib.h>

#include "lib/libft/libft.h"
#include "lib/parse/src/parse.h"
#include "lib/tokenize/tokenize.h"

void remove_empty(token **head) {
  token *it = *head;
  while (it) {
    token *next = it->next;
    if (it->str && it->str[0] == '\0') {
      token_free(token_lst_remove(head, it));
    }
    it = next;
  }
}

void word_join(token **head) {
  token *it = *head;
  while (it != NULL && it->next != NULL) {
    if (it->flags & TOK_RIGHT_JOIN && it->next->flags & TOK_LEFT_JOIN) {
      it->flags &= it->next->flags;
      char *new_str = ft_strjoin(it->str, it->next->str);
      free(it->str);
      token_free(token_lst_remove(head, it->next));
      it->str = new_str;
    } else {
      it = it->next;
    }
  }
}
