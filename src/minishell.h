#ifndef SRC_MINISHELL_H_
#define SRC_MINISHELL_H_

#include "lib/environ/environ.h"
#include "lib/tokenize/tokenize.h"
#include "lib/parse/parse.h"

int minishell();

int heredoc_replace(cmd *c);
void heredoc_cleanup(cmd *c);

#define SIG_DEFAULT 0
#define SIG_CHILD 1
#define SIG_EXE 2
#define SIG_HEREDOC 3
#define SIG_HEREDOC_CHILD 4

void set_signal(int mode);

#endif // SRC_MINISHELL_H_