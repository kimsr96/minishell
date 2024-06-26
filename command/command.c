/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:17 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/26 22:36:06 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	execute_cmd(t_block *block, t_env_list *env)
{
	pid_t		pid;
	t_command	*cmd;

	if (check_cmd(block, env)) //built_in
		return ;
	else
	{
		cmd = block->command;
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			if (execve(cmd->cmd_path, cmd->target, NULL) == -1)
				perror(*block->command->target);
		}
		else
			printf("nothing\n");
			// waitpid(pid, &status, 0);	
	}
}
