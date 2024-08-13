/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:25:17 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/13 17:05:30 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

int	handle_redirection(t_command *cmd)
{
	t_command	*cur;
	t_redirect	*redir;

	cur = cmd;
	redir = cur->redirect;
	if (cur != NULL)
	{
		while (redir != NULL)
		{
			if (redirect(redir) < 0)
				return (-1);
			redir = redir->next;
		}
	}
	return (1);
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
	t_pipe	p;
	int		stdin_backup;
	int		stdout_backup;

	init_pipe(&p, block);
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (p.pipe_num == 0)
		exec_no_pipe(block, env, &p);
	else
		exec_with_pipe(block, env, &p);
	restore_fd(stdin_backup, stdout_backup);
}

void	execute_in_child(t_block *block, t_env_list *env)
{
	int		status;
	char	**envp;

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
	pid_t	pid;

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
			{
				p->child_num++;
				pid = fork();
				if (pid < 0)
					perror("fork error");
				else if (pid == 0)
				{
					if (handle_redirection(cur->command) < 0)
						exit(EXIT_FAILURE);
					execute_in_child(cur, env);
				}
				else
					wait_process(p, env, pid);
			}
		}
		cur = cur->next;
	}
}

void	exec_with_pipe(t_block *block, t_env_list *env, t_pipe *p)
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
					perror("pipe error\n");
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

pid_t	fork_process(t_block *block, t_env_list *env, t_pipe *p)
{
	pid_t	pid;
	t_block	*cur;

	cur = block;
	pid = fork();
	if (pid < 0)
		perror("fork error");
	else if (pid == 0)
	{
		if (p->pipe_after)
		{
			dup2(p->fds[1], STDOUT_FILENO);
			close(p->fds[1]);
		}
		if (p->pipe_prev)
		{
			dup2(p->prev_fd, STDIN_FILENO);
			close(p->prev_fd);
		}
		close(p->fds[0]);
		// handle_redirection(cur->command);
		execute_in_child(cur, env);
	}
	else
	{
		if (p->fds[1] != 0)
			close(p->fds[1]);
		if (p->prev_fd != -1)
			close(p->prev_fd);
	}
	return (pid);
}

void	wait_process(t_pipe *p, t_env_list *env, pid_t last_pid)
{
	int		i;
	int		status;
	int		exit_code;
	pid_t	pid;

	i = 0;
	while (i < p->child_num)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
			{
				exit_code = WEXITSTATUS(status);
				update_exit_code(exit_code, env);
			}
			else if (WIFSIGNALED(status))
			{
				exit_code = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
				update_exit_code(exit_code, env);
			}
		}
		i++;
	}
}

void	update_exit_code(int exit_code, t_env_list *env)
{
	if (env->value != NULL)
	{
		free(env->value);
		env->value = NULL;
	}
	env->value = ft_itoa(exit_code);
}

void	init_pipe(t_pipe *p, t_block *block)
{
	p->prev_fd = -1;
	p->pipe_num = get_pipe_num(block);
	p->pipe_after = 1;
	p->pipe_prev = 0;
	p->child_num = 0;
}
