/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:05:12 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/08 09:26:20 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_parser	*pipe_parser(void)
{
	t_parser	*parser;

	parser = new_parser(PIPE);
	ft_memset(parser, 0, sizeof(parser));
	return (parser);
}

static t_parser	*redirect_parser(t_token *token, t_tokentype type)
{
	t_parser	*parser;
	t_redirect	*redirect;

	parser = new_parser(type);
	ft_memset(parser, 0, sizeof(parser));
	redirect = malloc(sizeof(t_redirect));
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
	ft_memset(parser, 0, sizeof(parser));
	command = malloc(sizeof(t_command));
	ft_memset(command, 0, sizeof(command));
	command->target = NULL;
	if (!command)
		exit(1);
	while (curr && curr->type != PIPE && \
		curr->type != IN_REDIRECT && curr->type != OUT_REDIRECT)
	{	
		command->target = join_str(command->target, curr->data);
		curr = curr->next;
	}
	add_cmd_path(command);
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
			parser = pipe_parser();
			add_back_parser(head, parser);
		}
		else if (curr->type == IN_REDIRECT || curr->type == OUT_REDIRECT)
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
