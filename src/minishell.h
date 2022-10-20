#ifndef SRC_MINISHELL_H_
#define SRC_MINISHELL_H_

#include "lib/environ/environ.h"
#include "lib/tokenize/tokenize.h"
#include "lib/parse/parse.h"

int minishell();

int heredoc_replace(token *c);
void heredoc_cleanup(token *c);

#define SIG_READLINE 0
#define SIG_SUBSHELL 1
#define SIG_EXE 2
#define SIG_HEREDOC 3
#define SIG_HEREDOC_CHILD 4

void set_signal(int mode);
void set_termios(int mode);

#endif // SRC_MINISHELL_H_
