#include <stdlib.h>

#include "lib/tokenize/src/tokenize.h"

void token_lst_push_back(token **lst, token *new_token) {
  token *it = *lst;
  new_token->next = NULL;
  if (*lst == NULL) {
    *lst = new_token;
    new_token->prev = NULL;
  } else {
    it = *lst;
    while (it->next != NULL) it = it->next;
    it->next = new_token;
    new_token->prev = it;
  }
  it = *lst;
}

token *token_lst_remove(token **head, token *remove) {
  if (head && remove == *head) {
    *head = remove->next;
    return remove;
  }
  if (remove->prev) remove->prev->next = remove->next;
  if (remove->next) remove->next->prev = remove->prev;
  return remove;
}

void token_free(token *tok) {
  free(tok->str);
  free(tok);
}

void token_lst_free(token **head) {
  token *it = *head;
  while (it) {
    token *next = it->next;
    token_free(it);
    it = next;
  }
  *head = NULL;
}
