#ifndef SRC_MINISHELL_H_
#define SRC_MINISHELL_H_

#include "lib/environ/environ.h"
#include "lib/tokenize/tokenize.h"
#include "lib/parse/parse.h"

int minishell();

int heredoc_replace(cmd *c);
void heredoc_cleanup(cmd *c);

#endif // SRC_MINISHELL_H_
