/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:05:12 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/11 17:14:54 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_command	*new_command(t_token *token, t_env_list *env)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		exit(1);
	cmd->is_empty = 1;
	cmd->target = NULL;
	cmd->redirect = NULL;
	if (token->type == CMD)
	{
		cmd->is_empty = 0;
		cmd->cmd_path = get_cmd(env, token->data);
	}
	return (cmd);
}

static int	redirect_parser(t_block *block, t_token *token, t_env_list *env)
{
	t_redirect	*redir;

	if (!token->next || token->next->type == PIPE)
		return (parsing_error(env, ERR_SYNTAX, 1));
	token->type = set_redirect_type(token->data);
	redir = get_redir(token, token->type);
	if (!redir)
	{
		token->err = 1;
		return (1);
	}
	add_back_redirect(&block->command->redirect, redir);
	return (0);
}

static t_token	*command_parser(t_block **head, t_token *curr, t_env_list *env)
{
	t_block		*block;

	block = new_block(CMD);
	block->command = new_command(curr, env);
	while (curr)
	{
		if (is_redirect(curr->type))
		{
			if (redirect_parser(block, curr, env))
				return (NULL);
			curr = curr->next;
		}
		else
			block->command->target = join_str \
									(block->command->target, curr->data);
		if (curr->next)
			if (curr->next->type == PIPE)
				break ;
		curr = curr->next;
	}
	env_exception(block->command);
	add_back_block(head, block);
	return (curr);
}

int	parsing_token(t_block **b_head, t_token **t_head, t_env_list *env)
{
	t_token		*curr;
	t_block		*block;

	curr = *t_head;
	*b_head = NULL;
	while (curr)
	{
		if (curr->type == PIPE)
		{
			block = new_block(PIPE);
			add_back_block(b_head, block);
		}
		else
			curr = command_parser(b_head, curr, env);
		if (curr)
			curr = curr->next;
	}
	if (block_err_exception(b_head, t_head, env))
		return (1);
	return (0);
}
