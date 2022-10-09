#include "lib/parse/src/parse.h"

#include <stdio.h>
#include <stdlib.h>

cmd *parse(token *tok) {
  // remove_empty(&tok);
  word_join(&tok);
  cmd *head = convert_to_command(tok);
  cmd *it = head;
  while (it) {
    if (extract_redirection(it)) {
      fprintf(stderr, "no breaking please\n");
      return 0;
    }
    it = it->next;
  }
  if (getenv("DEBUG")) {
    debug_cmd_print(head);
  }
  return head;
}
