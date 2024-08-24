/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:38:57 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/24 14:50:14 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_heredoc(t_block *block, t_env_list *env)
{
	t_block		*cur;
	t_redirect	*redir;

	cur = block;
	while (cur != NULL)
	{
		if (cur->type == CMD)
		{
			redir = cur->command->redirect;
			while (redir != NULL)
			{
				if (redir->io_type == HEREDOC_REDIRECT)
					exec_heredoc(redir, env);
				if (redir->file_name == NULL)
					return (1);
				redir = redir->next;
			}
		}
		cur = cur->next;
	}
	return (0);
}

void	exec_heredoc(t_redirect *redir, t_env_list *env)
{
	pid_t	pid;
	int		status;
	char	*filename;

	filename = get_tmp_filename();
	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
	{
		get_heredoc(redir, env, filename);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			unlink_if_sigint(filename, redir, env);
			return ;
		}
		redir->file_name = filename;
	}
}

void	unlink_if_sigint(char *filename, t_redirect *redir, t_env_list *env)
{
	unlink(filename);
	free(filename);
	redir->file_name = NULL;
	ft_putendl_fd("", 1);
	update_exit_code(1, env);
}

void	get_heredoc(t_redirect *redir, t_env_list *env, char *filename)
{
	char	*line;
	char	*delimiter;
	char	*ret;
	int		fd;

	signal(SIGINT, SIG_DFL);
	delimiter = redir->delimiter;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)) && \
			ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break ;
		}
		ret = heredoc_env_expansion(env, line, redir->heredoc_expansion);
		ft_putendl_fd(ret, fd);
		free(line);
		free(ret);
	}
	close(fd);
}
