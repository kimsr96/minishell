/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:32:28 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/24 15:37:51 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "./built_in/built_in.h"
# include "../env/env.h"

int status;

/* command.c */
void	execute_cmd(t_parser *parser, t_env_list *env);

#endif