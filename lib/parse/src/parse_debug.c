#include <stdio.h>

#include "lib/parse/src/parse.h"

static void debug_cmd_redirect(token *redir) {
  while (redir) {
    printf("\033[1;42m");
    if (redir->flags & TOK_WRITE)
      printf(">");
    else if (redir->flags & TOK_APPEND)
      printf(">>");
    else if (redir->flags & TOK_READ)
      printf("<");
    else if (redir->flags & TOK_HEREDOC)
      printf("<<");
    else
      printf("WTF");
    if (redir->flags & (TOK_SINGLE_QUOTED | TOK_DOUBLE_QUOTED))
      printf(" \"%s\"\033[0;m |", redir->str);
    else
      printf(" %s\033[0;m |", redir->str);
    redir = redir->next;
  }
}

void debug_cmd_print(cmd *command) {
  printf("\033[1;43m");
  printf("%-100s", "       Commands");
  printf("\033[0m\n");
  cmd *last;
  while (command) {
    token *it = command->simple_cmd;
    while (it) {
      if (it->str)
        printf("%s | ", it->str);
      else
        printf("no command :( | ");
      it = it->next;
    }
    debug_cmd_redirect(command->redirect_input);
    debug_cmd_redirect(command->redirect_output);
    command = command->next;
    printf("\n");
  }
}
