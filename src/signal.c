#include <signal.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "lib/environ/environ.h"
#include "lib/readline/readline.h"
#include "src/minishell.h"

void sigint_handler(int signo) {
  if (signo == SIGINT) {
    environ_add("?=130");
    write(2, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
  }
}

void sigint_handler_print_newline(int signo) {
  environ_add("?=130");
  if (signo == SIGINT) write(2, "\n", 1);
}

void set_signal(int sig) {
  signal(SIGQUIT, SIG_DFL);
  // fprintf(stderr, "setting signal mode to %d\n", sig);
  if (sig == SIG_CHILD) signal(SIGINT, SIG_IGN);
  if (sig == SIG_DEFAULT) signal(SIGINT, sigint_handler);
  if (sig == SIG_HEREDOC) signal(SIGINT, sigint_handler_print_newline);
  if (sig == SIG_HEREDOC_CHILD) signal(SIGINT, SIG_DFL);
  if (sig == SIG_EXE) signal(SIGINT, SIG_DFL);
  // if (sig == SIG_EXE) {
  //   signal(SIGQUIT, SIG_DFL);
  //   signal(SIGINT, SIG_DFL);
  // }
}

// void set_termios(int mode) {
//   struct termios term_setting;

//   tcgetattr(STDOUT_FILENO, &term_setting);
//   if (mode == MINISHELL_NO_CHILD || mode == MINISHELL_HAS_CHILD ||
//       mode == HEREDOC_PARENT || mode == HEREDOC_CHILD)
//     term_setting.c_lflag &= ~(ECHOCTL);
//   else if (mode == EXECUTE_CHILD)
//     term_setting.c_lflag |= ECHOCTL;
//   tcsetattr(STDOUT_FILENO, NONE, &term_setting);
// }
