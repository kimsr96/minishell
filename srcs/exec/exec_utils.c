/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:56:35 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/14 16:59:27 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	restore_fd(int stdin_backup, int stdout_backup)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

int	get_pipe_num(t_block *block)
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
