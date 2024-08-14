/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:22:24 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/14 16:59:27 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	wait_process(t_pipe *p, t_env_list *env, pid_t last_pid)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < p->child_num)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
			{
				update_exit_code(WEXITSTATUS(status), env);
			}
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
				update_exit_code(128 + WTERMSIG(status), env);
			}
		}
		i++;
	}
}
