/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:32:28 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/13 20:51:05 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "built_in.h"
# include "exec.h"
# include "env.h"
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
int		handle_redirection(t_command *cmd);
void	exec(t_block *block, t_env_list *env);
void	execute_in_child(t_block *block, t_env_list *env);
void	exec_no_pipe(t_block *block, t_env_list *env, t_pipe *p);
void	exec_with_pipe(t_block *block, t_env_list *env, t_pipe *p);
void	init_pipe(t_pipe *p, t_block *block);
void	restore_fd(int stdin_backup, int stdout_backup);
pid_t	fork_process(t_block *block, t_env_list *env, t_pipe *p);
void	wait_process(t_pipe *p, t_env_list *env, pid_t last_pid);
void	update_exit_code(int exit_code, t_env_list *env);

int		check_heredoc(t_block *block, t_env_list *env);
void	exec_heredoc(t_redirect *redir, t_env_list *env);
void	get_heredoc(t_redirect *redir, char *filename);
char	*get_tmp_filename(void);
void	unlink_tmpfile(t_block *block);

int		check_cmd_error(t_block *block);
int		is_exist_file(char *path);
int		is_executable(char *path);

#endif