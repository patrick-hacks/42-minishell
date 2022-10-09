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

static const char promt[] = {0xE2, 0x9E, 0x9C, ' ', '\0'};

int execute_after_heredoc(cmd *c) {
  heredoc_replace(c);
  if (getenv("DEBUG")) {
    debug_cmd_print(c);
  }
  execute(c);
  heredoc_cleanup(c);
}

int minishell() {
  environ_init();
  while (1) {
    set_signal(SIG_DEFAULT);
    char *line = readline(promt);
    set_signal(SIG_CHILD);
    if (!line || !ft_strncmp(line, "", 2)) continue;
    add_history(line);
    token *tokens = tokenize(line);
    free(line);
    if (!tokens) break;
    parse_expand_token(tokens);
    cmd *commands = parse(tokens);
    execute_after_heredoc(commands);
    parse_lst_free(&commands);
  }
  environ_cleanup();
  return (0);
}
