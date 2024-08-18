/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:56:40 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/18 16:07:53 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec(t_block *block, t_env_list *env)
{
	t_pipe	p;
	int		stdin_backup;
	int		stdout_backup;

	init_pipe(&p, block);
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (p.pipe_num == 0)
		exec_no_pipe(block, env, &p);
	else
		exec_has_pipe(block, env, &p);
	restore_fd(stdin_backup, stdout_backup);
}

void	execute_in_child(t_block *block, t_env_list *env)
{
	int		status;
	char	**envp;

	set_terminal_print(ON);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (handle_redirection(block->command) < 0)
		exit (EXIT_FAILURE);
	if (block->command->is_empty)
		exit(EXIT_SUCCESS);
	if (is_builtin(block))
	{
		status = exec_builtin(block, env, 1);
		exit(status);
	}
	status = check_cmd_error(block);
	if (status > 0)
		exit(status);
	else
	{
		envp = get_envp(env);
		if (execve(block->command->cmd_path, block->command->argv, envp) < 0)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
}

void	exec_no_pipe(t_block *block, t_env_list *env, t_pipe *p)
{
	t_block	*cur;

	cur = block;
	while (cur != NULL)
	{
		if (cur->type == CMD)
		{
			if (!cur->command->is_empty && is_builtin(cur))
			{
				if (handle_redirection(cur->command) < 0)
					update_exit_code(EXIT_FAILURE, env);
				else
					update_exit_code(exec_builtin(cur, env, 0), env);
			}
			else
				fork_no_pipe(cur, env, p);
		}
		cur = cur->next;
	}
}

void	exec_has_pipe(t_block *block, t_env_list *env, t_pipe *p)
{
	t_block	*cur;
	pid_t	last_pid;

	cur = block;
	while (cur != NULL)
	{
		if (cur->type == CMD)
		{
			if (cur->next != NULL && cur->next->type == PIPE)
			{
				if (pipe(p->fds) < 0)
					exit(1);
			}
			else
				p->pipe_after = 0;
			last_pid = fork_process(cur, env, p);
			p->prev_fd = p->fds[0];
			p->child_num++;
		}
		else if (cur->type == PIPE)
			p->pipe_prev = 1;
		cur = cur->next;
	}
	wait_process(p, env, last_pid);
}
