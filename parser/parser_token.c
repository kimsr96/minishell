/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:05:12 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/26 16:51:28 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_parser	*redirect_parser(t_token *token, t_tokentype type)
{
	t_parser	*parser;
	t_redirect	*redirect;

	parser = new_parser(type);
	if (!parser)
		exit(1);
	redirect = ft_calloc(1, sizeof(t_redirect));
	if (!redirect)
		exit(1);
	redirect->io_type = type;
	redirect->file_name = token->next->data;
	parser->redirection = redirect;
	return (parser);
}

static t_token	*command_parser(t_parser **head, t_token *curr)
{
	t_parser	*parser;
	t_command	*command;

	parser = new_parser(CMD);
	if (!parser)
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
	parser->command = command;
	add_back_parser(head, parser);
	return (curr);
}

void	parsing_token(t_parser **head, t_token *tokens)
{
	t_token		*curr;
	t_parser	*parser;

	curr = tokens;
	*head = NULL;
	while (curr)
	{
		if (curr->type == PIPE)
		{
			parser = new_parser(PIPE);
			add_back_parser(head, parser);
		}
		else if (curr->type == IN_REDIRECT || curr->type == OUT_REDIRECT || \
				curr->type == HEREDOC_REDIRECT || curr->type == APPEND_REDIRECT)
		{
			parser = redirect_parser(curr, curr->type);
			curr = curr->next;
			add_back_parser(head, parser);
		}
		else
			curr = command_parser(head, curr);
		if (curr)
			curr = curr->next;
	}
}
