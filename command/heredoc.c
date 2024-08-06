/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:38:57 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/06 18:04:16 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	check_heredoc(t_block *block)
{
	t_block		*cur;
	t_redirect	*redir;
	pid_t		pid;

	cur = block;
	while (cur != NULL)
	{
		if (cur->type == CMD)
		{
			redir = cur->command->redirect;
			while (redir != NULL)
			{
				if (redir->io_type == HEREDOC_REDIRECT)
				{
					pid = fork();
					if (pid < 0)
						exit(1);
					else if (pid == 0)
						redir->file_name = get_heredoc(redir);
					else
						waitpid(pid, NULL, 0);
				}
				redir = redir->next;
			}
		}
		cur = cur->next;
	}
}

char	*get_heredoc(t_redirect *redir)
{
	char	*tmpfile;
	char	*line;
	char	*delimiter;
	int		fd;

	signal(SIGINT, SIG_DFL);
	tmpfile = get_tmp_filename();
	delimiter = redir->delimiter;
	fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)) && \
			ft_strlen(line) == ft_strlen(delimiter))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (tmpfile);
}

char	*get_tmp_filename(void)
{
	int		count;
	char	*count_str;
	char	*filename;

	count = 0;
	while (1)
	{
		count_str = ft_itoa(count);
		filename = ft_strjoin(".minishell_tmp", count_str);
		free(count_str);
		if (access(filename, F_OK) == -1)
			break ;
		free(filename);
		count++;
	}
	return (filename);
}

void	unlink_tmpfile(t_block *block)
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
				{
					unlink(redir->file_name);
				}
				redir = redir->next;
			}
		}
		cur = cur->next;
	}
}
