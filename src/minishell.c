#include "src/minishell.h"

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib/environ/environ.h"
#include "lib/execute/execute.h"
#include "lib/libft/libft.h"
#include "lib/parse/parse.h"
#include "lib/tokenize/tokenize.h"
#include "lib/get_next_line/get_next_line.h"

// extern int(*rl_signal_event_hook)();

// int rl_signal() {
//   environ_add("?=130");
//   write(1, "\n", 1);
//   rl_set_prompt("\e[1;31m130\xE2\x9E\x9C\e[0m ");
//   rl_on_new_line();
//   rl_redisplay();
//   return 0;
// }

static char *pretty_readline() {
  set_signal(SIG_READLINE);
  if (!isatty(0)) return get_next_line(0);
  char *line = "";
  while (!line[0]) {
    char *ret = environ_get("?");
    char prompt[20];
    ft_strcpy(prompt, "\e[1;32m:) \xE2\x9E\x9C\e[0m ");
    if (ret && ret[0] != '0' && ft_strlen(ret) <= 5) {
      ft_strcpy(prompt, "\e[1;31m   \xE2\x9E\x9C\e[0m ");
      ft_memcpy(prompt + 7, ret, ft_strlen(ret));
    }
    line = readline(prompt);
    if (!line) return NULL;
  }
  add_history(line);
  return line;
}

static int bonus(token *tokens) {
  while (tokens) {
    if (tokens->flags & (TOK_AND | TOK_OR | TOK_BRACKET))
      return 1;
    tokens = tokens->next;
  }
  return 0;
}

int minishell() {
  environ_init();
  while (1) {
    char *line = pretty_readline();
    if (!line) break;
    token *tokens = tokenize(line);
    free(line);
    if (!tokens) continue;
    if (bonus(tokens)) continue;
    parse_expand_token(tokens);
    cmd *commands = parse(tokens);
    if (heredoc_replace(commands) == 0) {
      execute(commands);
    }
    heredoc_cleanup(commands);
    parse_lst_free(&commands);
  }
  int ret = ft_atoi(environ_get("?"));
  environ_cleanup();
  return (ret);
}
