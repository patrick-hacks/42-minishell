#include <stdio.h>

#include "lib/tokenize/src/tokenize.h"

static void debug_token_flag(token *tokens, int flag) {
  if (tokens->flags & flag)
    printf(" \033[1;41m    \033[0m |");
  else
    printf("      |");
}

void debug_token_print(token *tokens) {
  printf("\033[1;43m");
  printf(
      "       String       || Word | Sing | Doub | Brac | Left | Righ | "
      "Read | Writ | Appe | Here | Pipe |  AND |  OR  |");
  printf("\033[0m\n");
  while (tokens) {
    if (tokens->flags & TOK_WORD)
      printf("%-20s||", tokens->str);
    else
      printf("%-20c||", ' ');
    int i = 1;
    while (i <= TOK_OR) {
      debug_token_flag(tokens, i);
      i <<= 1;
    }
    tokens = tokens->next;
    printf("\n");
  }
}
