/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:50:12 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/11 15:12:20 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../command.h"

void	execute_cmd(t_parser *parser)
{
	int			status;
	pid_t		pid;
	t_command	*cmd;

	check_cmd(parser);
	cmd = parser->command;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		if (execve(cmd->cmd_path, cmd->target, NULL) == -1)
			perror("execve");
	}
	else
		waitpid(pid, &status, 0);
}
