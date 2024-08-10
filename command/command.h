/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:32:28 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/10 13:58:44 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "./built_in/built_in.h"
# include "./exec/exec.h"
# include "../env/env.h"
# include <readline/readline.h>
# include <fcntl.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_pipe
{
	int	fds[2];
	int	prev_fd;
	int	pipe_num;
	int	pipe_after;
	int	pipe_prev;
	int	child_num;
}t_pipe;

/* command.c */
void	handle_redirection(t_command *cmd);
void	exec(t_block *block, t_env_list *env);
void	execute_in_child(t_block *block, t_env_list *env);
void	exec_no_pipe(t_block *block, t_env_list *env, t_pipe *p);
void	exec_with_pipe(t_block *block, t_env_list *env, t_pipe *p);
void	init_pipe(t_pipe *p, t_block *block);
void	restore_fd(int stdin_backup, int stdout_backup);
void	fork_process(t_block *block, t_env_list *env, t_pipe *p);
void	child_process(t_block *block, int *fds, t_env_list *env, int prev_fd);
void	wait_process(t_pipe *p, t_env_list *env);
void	update_exit_code(int exit_code, t_env_list *env);

void	check_heredoc(t_block *block);
void	exec_heredoc(t_redirect *redir);
void	get_heredoc(t_redirect *redir, char *filename);
char	*get_tmp_filename(void);
void	unlink_tmpfile(t_block *block);

int     g_status;
#endif