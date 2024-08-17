/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:38:00 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/17 16:38:18 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
					unlink(redir->file_name);
				redir = redir->next;
			}
		}
		cur = cur->next;
	}
}
