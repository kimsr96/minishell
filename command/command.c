/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:17 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/15 15:39:12 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	execute_cmd(t_parser *parser, t_env_list *env)
{
	int			status;
	pid_t		pid;
	t_command	*cmd;

	if (check_cmd(parser, env))
		return ;
	else
	{
		cmd = parser->command;
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			if (execve(cmd->cmd_path, cmd->target, NULL) == -1)
				perror(*parser->command->target);
		}
		else
			waitpid(pid, &status, 0);
	}
}
