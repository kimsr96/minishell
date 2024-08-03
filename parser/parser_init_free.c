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

void	free_block(t_block *block)
{
	t_command	*cmd;

	cmd = block->command;
	if (cmd)
	{
		if (cmd->redirect)
		{
			if (cmd->redirect->delimiter)
				free(cmd->redirect->delimiter);
			if (cmd->redirect->file_name)
				free(cmd->redirect->delimiter);
			free(cmd->redirect);
		}
		if (block->command->cmd_path)
			free(block->command->cmd_path);
		if (block->command->target)
			free_2darr(block->command->target);
		free(block->command);
	}
	free(block);
}
