/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:17 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/30 21:41:26 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	handle_redirection(t_block *block)
{
	t_block	*tmp;

	tmp = block;
	while (tmp != NULL && tmp->type != PIPE)
	{
		if (tmp->redirection != NULL)
		{
			if (redirect(tmp) < 0)
				exit (1);
		}
		tmp = tmp->next;
	}
}

void	restore_fd(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

void	exec(t_block *block, t_env_list *env)
{
	t_block	*cur;
	int		fds[2];
	int		check_redir;
	int		stdin_backup;
	int		stdout_backup;

	//stdin, stdout 백업필요
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	cur = block;
	check_redir = 0;
	while (cur != NULL)
	{
		if (!check_redir)
		{
			handle_redirection(cur);
			check_redir = 1;
		}
		if (cur->type == CMD)
		{
			if (is_builtin(cur))
				exec_builtin(cur, env);
			else
				fork_process(cur, fds);
		}
		if (cur->next != NULL && cur->next->type == PIPE)
		{
			if (pipe(fds) < 0)
			{
				perror("pipe error");
			}
			close(fds[1]);
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
			check_redir = 0;
		}
		cur = cur->next;
	}
	restore_fd(stdin_backup, stdout_backup);
}

void	fork_process(t_block *block, int fds[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("fork error");
	else if (pid == 0)
		child_process(block, fds);
	else
		parent_process(pid);
}

void	child_process(t_block *block, int fds[2])
{
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	if (!block->command->cmd_path)
		perror("command not found");
	if (execve(block->command->cmd_path, block->command->target, NULL) < 0)
		perror("exec error");
}

void	parent_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
}
