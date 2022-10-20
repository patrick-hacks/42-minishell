#include <stdbool.h>
#include <stdio.h>

#include "lib/environ/environ.h"
#include "lib/libft/libft.h"
#include "lib/tokenize/src/tokenize.h"

typedef struct s_token_id {
  char token_str[3];
  int id;
} t_token_id;

typedef struct s_token_range {
  char begin;
  char end;
  int id;
} t_token_range;

static const char *meta_chars = "\'\"|<> \n\t";
static const char *meta_join = "|<>()& \n\t";
static const t_token_id token_ids[] = {
    {">>", TOK_REDIRECT &TOK_APPEND},
    {">", TOK_REDIRECT &TOK_WRITE},
    {"<<", TOK_REDIRECT &TOK_HEREDOC},
    {"<", TOK_REDIRECT &TOK_READ},
    {"||", TOK_OR},
    {"&&", TOK_AND},
    {"|", TOK_PIPE},
};
static const t_token_range range[] = {
    {'"', '"', TOK_DOUBLE_QUOTED | TOK_WORD},
    {'\'', '\'', TOK_SINGLE_QUOTED | TOK_WORD},
    {'(', ')', TOK_BRACKET | TOK_WORD},
};

static int is_joined(char *line, int i) {
  if (i < 0 || line[i] == '\0') return false;
  if (ft_strchr(meta_join, line[i])) return false;
  return true;
}

int get_range(token *tok, char *line, int *it) {
  int i = 0;
  while (i < (int)((sizeof(range)) / sizeof(t_token_range))) {
    if (range[i].begin == line[*it]) {
      tok->flags = range[i].id;
      char *end = ft_strchr(line + *it + 1, range[i].end);
      tok->str = ft_strsub_or_die(line + *it, 1, end - line - 1);
      if (is_joined(line + *it, -1)) tok->flags |= TOK_LEFT_JOIN;
      if (is_joined(line + *it, end - line + 1)) tok->flags |= TOK_RIGHT_JOIN;
      *it += end - line + 1;
      return 0;
    }
    i += 1;
  }
  return 1;
}

int get_special(token *tok, char *line, int *it) {
  int i = 0;
  while (i < (int)(sizeof(token_ids) / sizeof(t_token_id))) {
    if (ft_strncmp(token_ids[i].token_str, line,
                   ft_strlen(token_ids[i].token_str)) == 0) {
      tok->flags = token_ids[i].id;
      *it += ft_strlen(token_ids[i].token_str);
      return 0;
    }
    i += 1;
  }
  return 1;
}

int get_default(token *tok, char *line, int *it) {
  tok->flags |= TOK_WORD;
  int start = *it;
  while (!ft_strchr(meta_chars, line[*it])) *it += 1;
  tok->str = ft_strsub_or_die(line, start, *it - start);
  if (is_joined(line, start - 1)) tok->flags |= TOK_LEFT_JOIN;
  if (is_joined(line, *it)) tok->flags |= TOK_RIGHT_JOIN;
  return 0;
}
