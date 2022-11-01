/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azakizad <azakizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:16:27 by pfuchs            #+#    #+#             */
/*   Updated: 2022/11/01 06:26:41 by azakizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_PARSE_H
# define P_PARSE_H

# include "lib/parse/parse.h"

t_cmd	*convert_to_command(t_token *tok);
int		extract_redirection(t_cmd *cmd, t_token *tok);
void	word_join(t_token **head);

void	debug_cmd_print(t_cmd *command);

#endif // P_PARSE_H_
