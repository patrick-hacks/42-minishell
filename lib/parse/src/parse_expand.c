#include <dirent.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "lib/environ/environ.h"
#include "lib/libft/libft.h"
#include "lib/tokenize/tokenize.h"

static int replace(char **str_pointer, int begin, int end) {
  char *str = *str_pointer;
  char tmp = str[end];
  str[end] = '\0';
  char *replacement = environ_get(str + begin + 1);
  if (!replacement) replacement = "";
  str[end] = tmp;
  int new_length = begin + ft_strlen(replacement) + (ft_strlen(str) - end);
  char *new_str = ft_calloc_or_die(1, new_length + 10);
  ft_strncpy(new_str, str, begin);
  ft_strcat(new_str, replacement);
  ft_strcat(new_str, str + end);
  free(str);
  *str_pointer = new_str;
  return begin + ft_strlen(replacement);
}

static void expand_env(token *token) {
  int i = 0;
  while (token->str[i]) {
    if (token->str[i] == '$') {
      int begin = i;
      while (token->str[i] && token->str[i] != ' ') i++;
      if (token->flags & TOK_RIGHT_JOIN &&
          !(token->flags & TOK_DOUBLE_QUOTED)) {
        i = replace(&token->str, begin, i) - 1;
      } else {
        if (i - begin > 1 && (token->str[1] != ' ' || token->str[1])) {
          i = replace(&token->str, begin, i) - 1;
        }
      }
    }
    i += 1;
  }
}

static int is_same_wildcard(char *wildcard_str, char *str) {
  if (!*str && !*wildcard_str) return 1;
  if (*str == *wildcard_str) {
    if (is_same_wildcard(wildcard_str + 1, str + 1)) return 1;
  }
  if (*wildcard_str == '*') {
    if (is_same_wildcard(wildcard_str + 1, str)) return 1;
    if (*str && is_same_wildcard(wildcard_str, str + 1)) return 1;
  }
  return 0;
}

static void remove_token(token *token_list) {
  token *remove = token_list->next;
  free(token_list->str);
  token_list->str = token_list->next->str;
  token_list->next = token_list->next->next;
  if (token_list->next->next) {
    token_list->next->next->prev = token_list;
  }
  free(remove);
}

static void insert_token(token *token_list, char *str) {
  token *new_token = ft_calloc_or_die(1, (sizeof(token)));
  new_token->str = ft_strdup(str);
  new_token->next = token_list->next;
  if (new_token->next) new_token->next->prev = new_token;
  new_token->prev = token_list;
  token_list->next = new_token;
}

static void expand_star(token *token) {
  if (ft_strchr(token->str, '*') == NULL) return;
  if (environ_get("PWD") == NULL) return;
  DIR *d = opendir(environ_get("PWD"));
  if (!d) return;
  bool expanded = false;
  struct dirent *dir = readdir(d);
  while (dir) {
    if (dir->d_name[0] != '.' && is_same_wildcard(token->str, dir->d_name)) {
      insert_token(token, dir->d_name);
      expanded = true;
    }
    dir = readdir(d);
  }
  if (expanded) remove_token(token);
}

void parse_expand_token(token *tokens) {
  token *it = tokens;
  while (it != NULL) {
    if ((it->flags & TOK_WORD) && !(it->flags & TOK_SINGLE_QUOTED)) {
      expand_env(it);
      expand_star(it);
    }
    it = it->next;
  }
}

int parse_expand_str(char **str) {
  int i = 0;
  while ((*str)[i]) {
    if ((*str)[i] == '$') {
      int begin = i;
      while ((*str)[i] && ft_strchr(" \t\n\"\'", (*str)[i]) == NULL) i++;
      i = replace(str, begin, i) - 1;
    }
    i += 1;
  }
  return 0;
}
