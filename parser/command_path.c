/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 09:25:07 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/21 14:42:51 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_cmd_path(t_command *command, char *cmd)
{
	char	*cmd_path;

	cmd_path = ft_strjoin("/bin/", cmd);
	command->cmd_path = cmd_path;
}
