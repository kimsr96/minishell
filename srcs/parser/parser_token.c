/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:05:12 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/17 21:37:30 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		exit(1);
	cmd->is_empty = 1;
	cmd->argv = NULL;
	cmd->redirect = NULL;
	return (cmd);
}

static int	redirect_parser(t_block *block, t_token *token)
{
	t_redirect	*redir;

	if (!token->next || token->next->type == PIPE)
	{
		token->err = 1;
		return (1);
	}
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
	block->command = new_command();
	while (curr)
	{
		if (is_redirect(curr->type))
		{
			if (!redirect_parser(block, curr))
				curr = curr->next;
		}
		else
		{
			block->command->is_empty = 0;
			join_str(block->command, env, curr->data);
		}
		if (curr->next)
			if (curr->next->type == PIPE)
				break ;
		curr = curr->next;
	}
	env_exception(block->command);
	add_back_block(head, block);
	return (curr);
}

int	parsing_token(t_block **b_head, t_env_list *env, char *str)
{
	t_token		*t_head;
	t_token		*curr;
	t_block		*block;

	t_head = NULL;
	*b_head = NULL;
	if (tokenizer(&t_head, str, env))
		return (free_all_token(t_head));
	curr = t_head;
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
	if (block_err(b_head, &t_head, env))
		return (free_all_token(t_head));
	free_all_token(t_head);
	return (0);
}
