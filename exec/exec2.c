/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:41:00 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/14 16:59:27 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	fork_no_pipe(t_block *cur, t_env_list *env, t_pipe *p)
{
	pid_t	pid;

	pid = fork();
	p->child_num++;
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
		set_pipe_stream(p);
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

void	set_pipe_stream(t_pipe *p)
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
}
