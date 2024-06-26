/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:32:28 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/26 22:22:22 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "./built_in/built_in.h"
# include "../env/env.h"

/* command.c */
void	execute_cmd(t_block *block, t_env_list *env);

int     g_status;
#endif