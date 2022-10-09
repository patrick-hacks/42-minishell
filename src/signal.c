#include <signal.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "lib/environ/environ.h"

// signal(SIGINT, SIG_DFL);
// signal(SIGQUIT, SIG_IGN);

//// asd
void signal_heredoc() {
  write(1, "\n", 1);
  /// TODO: cancel heredoc
}

void signal_readline() {
  write(1, "\n", 1);
  environ_add("exit=1");
  rl_replace_line("", 0);
  rl_on_new_line();
  rl_redisplay();
}

void signal_child() {

}

int signal_handler(void) {
  struct termios term;

  signal(SIGINT, signal_child);
  signal(SIGQUIT, signal_child);
  tcgetattr(1, &term);
  tcsetattr(1, 0, &term);
  return (0);
}
