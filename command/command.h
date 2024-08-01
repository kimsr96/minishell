/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:32:28 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/31 17:26:25 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "./built_in/built_in.h"
# include "./exec/exec.h"
# include "../env/env.h"

typedef struct s_pipe
{
	int	fds[2];
	int	prev_fd;
	int	stdin_backup;
	int	stdout_backup;
	int	pipe_num;
	int	pipe_after;
}t_pipe;

/* command.c */
void	handle_redirection(t_command *cmd);
void	exec(t_block *block, t_env_list *env);
void	execute_in_child(t_block *block, t_env_list *env);
void	exec_no_pipe(t_block *block, t_env_list *env);
void	exec_with_pipe(t_block *block, t_env_list *env);
void	init_pipe(t_pipe *p, t_block *block);
void	restore_fd(int stdin_backup, int stdout_backup);
void	fork_process(t_block *block, t_env_list *env, t_pipe *p);
void	child_process(t_block *block, int *fds, t_env_list *env, int prev_fd);
void	parent_process(pid_t pid);

int     g_status;
#endif