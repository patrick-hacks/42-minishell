/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfuchs <pfuchs@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:27 by pfuchs            #+#    #+#             */
/*   Updated: 2022/10/25 09:17:34 by pfuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_PARSE_SRC_PARSE_H_
# define LIB_PARSE_SRC_PARSE_H_

# include "lib/parse/parse.h"

cmd		*convert_to_command(token *tok);
int		extract_redirection(cmd *cmd);
void	word_join(token **head);

void	debug_cmd_print(cmd *command);

#endif // LIB_PARSE_SRC_PARSE_H_
