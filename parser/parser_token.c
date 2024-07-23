/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:05:12 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/23 19:58:57 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_token	*command_parser(t_block **head, t_token *curr, t_env_list *env)
{
	t_block		*block;
	t_command	*cmd;

	block = new_block(CMD);
	if (!block)
		exit(1);
	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		exit(1);
	cmd->target = NULL;
	cmd->redirect = NULL;
	cmd->cmd_path = get_cmd(env, curr->data);
	while (curr)
	{
		if (is_redirect(curr->type))
		{
			curr->type = set_redirect_type(curr->data);
			add_back_redirect(&cmd->redirect, get_redirect(curr, curr->type));
			curr = curr->next;
		}
		else
		{
			cmd->target = join_str(cmd->target, curr->data);
		}
		if (curr->next)
			if (curr->next->type == PIPE)
				break ;
		curr = curr->next;
	}
	block->command = cmd;
	add_back_block(head, block);
	return (curr);
}

void	parsing_token(t_block **head, t_token *tokens, t_env_list *env)
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
}
