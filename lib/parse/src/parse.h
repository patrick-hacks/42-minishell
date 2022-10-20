#ifndef LIB_PARSE_SRC_PARSE_H_
#define LIB_PARSE_SRC_PARSE_H_

#include "lib/parse/parse.h"

cmd *convert_to_command(token *tok);
int extract_redirection(cmd *cmd);
void word_join(token **head);

void debug_cmd_print(cmd *command);
void parse_lst_free(cmd **c);

#endif // LIB_PARSE_SRC_PARSE_H_
