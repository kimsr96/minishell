/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 09:25:07 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/30 21:20:49 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_cmd_path(t_command *command, char *cmd)
{
	char	*cmd_path;

	cmd_path = ft_strjoin("/bin/", cmd);
	command->cmd_path = cmd_path;
}
