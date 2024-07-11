/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:17 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/10 18:25:57 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	handle_redirection(t_block **head, t_block **cur)
{
	t_block	*next_block;
	t_block	*last_cmd;

	last_cmd = NULL;
	while ((*cur) != NULL && (*cur)->type != PIPE)
	{
		next_block = (*cur)->next;
		if ((*cur)->type == CMD)
			last_cmd = *cur;
		if ((*cur)->redirection != NULL)
		{
			if (redirect(head, *cur) < 0)
				exit (1);
		}
		(*cur) = next_block;
	}
	if (last_cmd != NULL)
		*cur = last_cmd;
}

void	restore_fd(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

// void	exec(t_block *block, t_env_list *env)
// {
// 	t_block	*cur;
// 	int		fds[2];
// 	int		check_redir;
// 	int		stdin_backup;
// 	int		stdout_backup;
// 	int		prev_fd;

// 	stdin_backup = dup(STDIN_FILENO);
// 	stdout_backup = dup(STDOUT_FILENO);
// 	cur = block;
// 	check_redir = 0;
// 	prev_fd = -1;
// 	while (cur != NULL)
// 	{
// 		if (!check_redir)
// 		{
// 			// restore_fd(stdin_backup, stdout_backup);
// 			handle_redirection(&block, &cur);
// 			check_redir = 1;
// 		}
// 		if (cur->next != NULL && cur->next->type == PIPE)
// 		{
// 			if (pipe(fds) < 0)
// 				perror("pipe error");
// 			if (cur->type == CMD)
// 			{
// 				if (is_builtin(cur))
// 					exec_builtin(cur, env);
// 				else
// 					fork_process(cur, fds, env, prev_fd);
// 			}
// 			if (prev_fd > 0)
// 				close(prev_fd);
// 			close(fds[1]);
// 			prev_fd = fds[0];
// 			dup2(prev_fd, STDIN_FILENO);
// 			cur = cur->next;
// 			check_redir = 0;
// 		}
// 		else
// 		{
// 			if (cur->type == CMD)
// 			{
// 				if (is_builtin(cur))
// 					exec_builtin(cur, env);
// 				else
// 					fork_process(cur, fds, env, prev_fd);
// 			}
// 		}
// 		cur = cur->next;
// 	}
// 	restore_fd(stdin_backup, stdout_backup);
// }

static int	has_pipe(t_block *block)
{
	t_block	*cur;

	cur = block;
	while (cur != NULL)
	{
		if (cur->type == PIPE)
			return (1);
		cur = cur->next;
	}
	return (0);
}
void	exec(t_block *block, t_env_list *env)
{
	t_block	*cur;
	int		fds[2];
	int		check_redir;
	int		stdin_backup;
	int		stdout_backup;
	int		prev_fd;
	int		has_pipe_flag;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	cur = block;
	check_redir = 0;
	prev_fd = -1;
	has_pipe_flag = has_pipe(block);
	while (cur != NULL)
	{
		if (!check_redir)
		{
			handle_redirection(&block, &cur);
			check_redir = 1;
		}
		if (cur->next != NULL && cur->next->type == PIPE)
		{
			if (pipe(fds) < 0)
				perror("pipe error");
		}
		if (cur->type == CMD)
		{
			if (!has_pipe_flag)
			{
				if (is_builtin(cur))
					exec_builtin(cur, env);
				else
					fork_process(cur, fds, env, prev_fd);
			}
			else
				fork_process(cur, fds, env, prev_fd);
			if (cur->next != NULL && cur->next->type == PIPE)
			{
				close(fds[1]);
				prev_fd = fds[0];
				dup2(prev_fd, STDIN_FILENO);
				check_redir = 0;
				cur = cur->next;
			}
		}
		cur = cur->next;
	}
	restore_fd(stdin_backup, stdout_backup);
}

void	fork_process(t_block *block, int *fds, t_env_list *env, int prev_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("fork error");
	else if (pid == 0)
		child_process(block, fds, env, prev_fd);
	else
		parent_process(pid);
}

void	child_process(t_block *block, int *fds, t_env_list *env, int prev_fd)
{
	char	**envp;

	if (prev_fd > 0)
	{
		// close(fds[0]);
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	// close(fds[1]);
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
	}
}

void	parent_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
}
