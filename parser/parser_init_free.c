/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_init_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:08:30 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/26 22:20:35 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_block(t_block *block)
{
	t_command	*cmd;
	t_redirect	*redir;
	t_redirect	*temp;

	cmd = block->command;
	if (cmd)
	{
		redir = cmd->redirect;
		while (redir)
		{
			temp = redir;
			if (redir->delimiter)
				free(redir->delimiter);
			if (redir->file_name)
				free(redir->file_name);
			redir = redir->next;
			free(temp);
		}
		if (block->command->cmd_path)
			free(block->command->cmd_path);
		if (block->command->argv)
			free_2darr(block->command->argv);
		free(block->command);
	}
	free(block);
}

void	free_block_all(t_block *block)
{
	t_block	*next;

	while (block)
	{
		next = block->next;
		free_block(block);
		block = next;
	}
}
