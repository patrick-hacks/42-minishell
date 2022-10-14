#include <stdlib.h>

#include "lib/libft/libft.h"
#include "lib/parse/src/parse.h"
#include "lib/tokenize/tokenize.h"

int extract_redirection(cmd *cmd) {
  token *tok = cmd->simple_cmd;
  while (tok) {
    if (tok->flags & TOK_REDIRECT) {
      token *name = tok->next;
      if (!name || !name->str) return 1;
      token *next = name->next;
      name->flags |= tok->flags;
      token_lst_remove(&cmd->simple_cmd, name);
      if (tok->flags & (TOK_READ | TOK_HEREDOC))
        token_lst_push_back(&cmd->redirect_input, name);
      if (tok->flags & (TOK_WRITE | TOK_APPEND))
        token_lst_push_back(&cmd->redirect_output, name);
      token_free(token_lst_remove(&cmd->simple_cmd, tok));
      tok = next;
    } else {
      tok = tok->next;
    }
  }
  return 0;
}

cmd *convert_to_command(token *tok) {
  cmd *head = ft_calloc_or_die(1, sizeof(cmd));
  head->simple_cmd = tok;
  cmd *cmd_it = head;
  while (tok != NULL) {
    token *next = tok->next;
    if (tok->flags & TOK_PIPE) {
      if (tok->prev) tok->prev->next = NULL;
      if (tok->next) tok->next->prev = NULL;
      token_free(tok);
      cmd_it->next = ft_calloc_or_die(1, sizeof(cmd));
      cmd_it->next->prev = cmd_it;
      cmd_it = cmd_it->next;
      cmd_it->simple_cmd = next;
    }
    tok = next;
  }
  return (head);
}
