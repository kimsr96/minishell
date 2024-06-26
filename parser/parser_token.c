/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:05:12 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/26 22:39:19 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_block	*redirect_block(t_token *token, t_tokentype type)
{
	t_block		*block;
	t_redirect	*redirect;

	block = new_block(type);
	if (!block)
		exit(1);
	redirect = ft_calloc(1, sizeof(t_redirect));
	if (!redirect)
		exit(1);
	redirect->io_type = type;
	redirect->file_name = token->next->data;
	block->redirection = redirect;
	return (block);
}

static t_token	*command_parser(t_block **head, t_token *curr)
{
	t_block		*block;
	t_command	*command;

	block = new_block(CMD);
	if (!block)
		exit(1);
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		exit(1);
	command->target = NULL;
	add_cmd_path(command, curr->data);
	while (curr)
	{	
		command->target = join_str(command->target, curr->data);
		if (curr->next)
			if (curr->next->type == PIPE || \
				curr->next->type == IN_REDIRECT \
				|| curr->next->type == OUT_REDIRECT)
				break ;
		curr = curr->next;
	}
	block->command = command;
	add_back_block(head, block);
	return (curr);
}

void	parsing_token(t_block **head, t_token *tokens)
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
		else if (curr->type == IN_REDIRECT || curr->type == OUT_REDIRECT || \
				curr->type == HEREDOC_REDIRECT || curr->type == APPEND_REDIRECT)
		{
			block = redirect_block(curr, curr->type);
			curr = curr->next;
			add_back_block(head, block);
		}
		else
			curr = command_parser(head, curr);
		if (curr)
			curr = curr->next;
	}
}
