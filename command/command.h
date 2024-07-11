/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:32:28 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/11 14:55:26 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "./built_in/built_in.h"
# include "./exec/exec.h"
# include "../env/env.h"

/* command.c */
void	handle_redirection(t_block **head, t_block **cur);
void	exec(t_block *block, t_env_list *env);
void	restore_fd(int stdin_backup, int stdout_backup);
void	fork_process(t_block *block, int *fds, t_env_list *env, int prev_fd);
void	child_process(t_block *block, int *fds, t_env_list *env, int prev_fd);
void	parent_process(pid_t pid);

int     g_status;
#endif