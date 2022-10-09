#include <stdbool.h>

#include "lib/environ/environ.h"
#include "lib/libft/libft.h"
#include "lib/tokenize/src/tokenize.h"

static const char *meta_chars = "\'\"|<> \n\t";
static const char *meta_join = "|<>";

static int is_joined(char *line, int i) {
  if (i < 0 || line[i] == '\0') return false;
  if (ft_strchr(environ_get("IFS"), line[i])) return false;
  if (ft_strchr(meta_join, line[i])) return false;
  return true;
}

token *get_quote(char *line, int *i) {
  token *tok = ft_calloc_or_die(1, sizeof(token));
  tok->flags = TOK_WORD;
  if (line[*i] == '\'') tok->flags |= TOK_SINGLE_QUOTED;
  if (line[*i] == '\"') tok->flags |= TOK_DOUBLE_QUOTED;
  int start = *i + 1;
  *i = ft_strchr(line + start, line[*i]) - line;
  tok->str = ft_strsub_or_die(line, start, *i - start);
  if (is_joined(line, start - 2)) tok->flags |= TOK_LEFT_JOIN;
  if (is_joined(line, *i + 1)) tok->flags |= TOK_RIGHT_JOIN;
  *i += 1;
  return (tok);
}

token *get_redirect(char *line, int *i) {
  token *new_token = ft_calloc_or_die(1, sizeof(token));
  if (ft_strncmp(line + *i, "<<", 2) == 0) {
    new_token->flags |= TOK_REDIRECT | TOK_HEREDOC;
    *i += 2;
  } else if (ft_strncmp(line + *i, ">>", 2) == 0) {
    new_token->flags |= TOK_REDIRECT | TOK_APPEND;
    *i += 2;
  } else if (ft_strncmp(line + *i, "<", 1) == 0) {
    new_token->flags |= TOK_REDIRECT | TOK_READ;
    *i += 1;
  } else if (ft_strncmp(line + *i, ">", 1) == 0) {
    new_token->flags |= TOK_REDIRECT | TOK_WRITE;
    *i += 1;
  }
  return new_token;
}

token *get_pipe(char *line, int *i) {
  token *new_token = ft_calloc_or_die(1, sizeof(token));

  new_token->flags |= TOK_PIPE;
  *i += 1;
  return new_token;
}

token *get_default(char *line, int *i) {
  token *tok = ft_calloc_or_die(1, sizeof(token));
  tok->flags |= TOK_WORD;
  int start = *i;
  while (!ft_strchr(meta_chars, line[*i])) *i += 1;
  tok->str = ft_strsub_or_die(line, start, *i - start);
  if (is_joined(line, start - 1)) tok->flags |= TOK_LEFT_JOIN;
  if (is_joined(line, *i)) tok->flags |= TOK_RIGHT_JOIN;
  return (tok);
}
