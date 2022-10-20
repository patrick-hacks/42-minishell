#include <stdio.h>

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

int main() {
  printf("%d\n", is_same_wildcard("*", "a"));
  printf("%d\n", is_same_wildcard("a*", "a"));
  printf("%d\n", is_same_wildcard("*a", "a"));
  printf("%d\n", is_same_wildcard("*a*", "a"));
  printf("%d\n", is_same_wildcard("a", "a"));
  printf("%d\n", is_same_wildcard("*a", "aa"));
  printf("%d\n", is_same_wildcard("a**a", "aba"));
  printf("NO\n");
  printf("%d\n", is_same_wildcard("*a", "ab"));
  printf("%d\n", is_same_wildcard("a*a*", "babab"));
}
