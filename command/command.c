/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:17 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/01 18:53:16 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	handle_redirection(t_command *cmd)
{
	if (cmd != NULL)
	{
		while (cmd->redirect != NULL)
		{
			if (redirect(cmd->redirect) < 0)
				exit (1);
			cmd->redirect = cmd->redirect->next;
		}
	}
}

void	restore_fd(int stdin_backup, int stdout_backup)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}
static int	get_pipe_num(t_block *block)
{
	int		pipe_num;
	t_block	*cur;

	pipe_num = 0;
	cur = block;
	while (cur != NULL)
	{
		if (cur->type == PIPE)
			pipe_num++;
		cur = cur->next;
	}
	return (pipe_num);
}

void	exec(t_block *block, t_env_list *env)
{
	int	pipe_num;
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	pipe_num = get_pipe_num(block);
	if (pipe_num == 0)
		exec_no_pipe(block, env);
	else
		exec_with_pipe(block, env);
	// while (pipe_num-- >= 0)
	// 	waitpid(-1, NULL, 0);
	restore_fd(stdin_backup, stdout_backup);
}

void	execute_in_child(t_block *block, t_env_list *env)
{
	char	**envp;

	if (!block->command->cmd_path)
		perror("command not found");
	if (is_builtin(block))
	{
		exec_builtin(block, env);
		exit(0);
	}
	else
	{
		envp = get_envp(env);
		if (execve(block->command->cmd_path, block->command->target, envp) < 0)
			perror("exec error");
		exit(0);
	}
}

void	exec_no_pipe(t_block *block, t_env_list *env)
{
	t_block	*cur;
	pid_t	pid;

	cur = block;
	while (cur != NULL)
	{
		handle_redirection(cur->command);
		if (cur->type == CMD)
		{
			if (is_builtin(cur))
				exec_builtin(cur, env);
			else
			{
				pid = fork();
				if (pid < 0)
					perror("fork error");
				else if (pid == 0)
					execute_in_child(cur, env);
				else
					waitpid(-1, NULL, 0);
			}
		}
		cur = cur->next;
	}
}

void	exec_with_pipe(t_block *block, t_env_list *env)
{
	t_block	*cur;
	t_pipe	p;

	init_pipe(&p, block);
	cur = block;
	while (cur != NULL)
	{
		if (cur->type == CMD)
		{
			if (cur->next != NULL && cur->next->type == PIPE)
			{
				if (pipe(p.fds) < 0)
					perror("pipe error\n");
			}
			else
				p.pipe_after = 0;
			fork_process(block, env, &p);
			p.prev_fd = p.fds[0];
			// dup2(p.stdin_backup, STDIN_FILENO);
		}
		cur = cur->next;
	}
}

void	fork_process(t_block *block, t_env_list *env, t_pipe *p)
{
	pid_t	pid;
	t_block	*cur;

	pid = fork();
	cur = block;
	if (pid < 0)
		perror("fork error");
	else if (pid == 0)
	{
		if (p->pipe_after)
		{
			dup2(p->fds[1], STDOUT_FILENO);
			close(p->fds[1]);
		}
		if (p->prev_fd != -1)
		{
			dup2(p->prev_fd, STDIN_FILENO);
			close(p->prev_fd);
		}
		close(p->fds[0]);
		handle_redirection(cur->command);
		execute_in_child(cur, env);
	}
	else
	{
		if (p->fds[1] != 0)
			close(p->fds[1]);
		if (p->prev_fd != -1)
			close(p->prev_fd);
		waitpid(-1, NULL, 0);
	}
}

void	init_pipe(t_pipe *p, t_block *block)
{
	p->prev_fd = -1;
	p->stdin_backup = dup(STDIN_FILENO);
	p->stdout_backup = dup(STDOUT_FILENO);
	p->pipe_num = get_pipe_num(block);
	p->pipe_after = 1;
}
