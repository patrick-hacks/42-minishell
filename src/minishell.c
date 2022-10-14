#include "src/minishell.h"

#include <stdio.h>
#include <stdlib.h>

#include "lib/environ/environ.h"
#include "lib/execute/execute.h"
#include "lib/libft/libft.h"
#include "lib/parse/parse.h"
#include "lib/readline/history.h"
#include "lib/readline/readline.h"
#include "lib/tokenize/tokenize.h"

static char *signal_readline() {
  char *line = NULL;
  set_signal(SIG_DEFAULT);
  char *ret = environ_get("?");
  char prompt[20];
  ft_strcpy(prompt, "\e[1;32m\xE2\x9E\x9C\e[0m ");
  if (ret && ret[0] != '0' && ft_strlen(ret) <= 5) {
    ft_strcpy(prompt, "\e[1;31m   \xE2\x9E\x9C\e[0m ");
    ft_memcpy(prompt + 7, ret, ft_strlen(ret));
  }
  while (!line || !line[0]) {
    line = readline(prompt);
  }
  set_signal(SIG_CHILD);
  add_history(line);
  return line;
}

int minishell() {
  environ_init();
  while (1) {
    char *line = signal_readline();
    token *tokens = tokenize(line);
    free(line);
    if (!tokens) continue;
    parse_expand_token(tokens);
    cmd *commands = parse(tokens);
    heredoc_replace(commands);
    execute(commands);
    heredoc_cleanup(commands);
    parse_lst_free(&commands);
  }
  environ_cleanup();
  return (0);
}
