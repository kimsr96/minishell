/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:05:12 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/07 16:18:05 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_command	*new_command(char *path)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		exit(1);
	cmd->target = NULL;
	cmd->redirect = NULL;
	cmd->cmd_path = path;
	return (cmd);
}

static t_token	*command_parser(t_block **head, t_token *curr, t_env_list *env)
{
	t_block		*block;
	t_redirect	*redir;

	block = new_block(CMD);
	block->command = new_command(get_cmd(env, curr->data));
	while (curr)
	{
		if (is_redirect(curr->type))
		{
			curr->type = set_redirect_type(curr->data);
			redir = get_redirect(curr, curr->type);
			if (!redir)
				return (NULL);
			add_back_redirect(&block->command->redirect, redir);
			curr = curr->next;
		}
		else
			block->command->target = join_str(block->command->target, curr->data);
		if (curr->next)
			if (curr->next->type == PIPE)
				break ;
		curr = curr->next;
	}
	env_exception(block->command);
	add_back_block(head, block);
	return (curr);
}

int	parsing_token(t_block **head, t_token *tokens, t_env_list *env)
{
	t_token		*curr;
	t_block		*block;

	curr = tokens;
	*head = NULL;
	while (curr)
	{
		if (curr->type == PIPE)
		{
			block = new_block(PIPE);
			add_back_block(head, block);
		}
		else
			curr = command_parser(head, curr, env);
		if (curr)
			curr = curr->next;
	}
	if (last_block_pipe_exception(head))
		return (1);
	return (0);
}
