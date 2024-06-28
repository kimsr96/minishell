/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:17 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/28 19:27:42 by hyeonble         ###   ########.fr       */
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

void	handle_redirection(t_block *block)
{
	t_block	*tmp;

	tmp = block;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (tmp->redirection != NULL)
		{
			if (redirect(block) < 0)
				exit (1);
		}
		tmp = tmp->next;
	}
}

void	exec(t_block *block, t_env_list *env)
{
	t_block	*cur;

	cur = block;
	while (cur != NULL)
	{
		if (cur->type == CMD && is_builtin(cur))
		{
			handle_redirection(cur);
			exec_builtin(cur, env);
			cur = cur->next;
		}
	}
}
