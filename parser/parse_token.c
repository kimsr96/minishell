/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:05:12 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/05 15:16:23 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser	*pipe_parser(t_token *token)
{
	t_parser	*parser;

	parser = new_parser(PIPE);
	ft_memset(parser, 0, sizeof(parser));
}

t_parser	*redirect_parser(t_token *token, t_tokentype type)
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
}

t_token	*command_parser(t_parser **head, t_token *curr)
{
	t_parser	*parser;
	t_command	*command;

	parser = new_parser(CMD);
	ft_memset(parser, 0, sizeof(parser));
	command = malloc(sizeof(t_command));
	command->target = NULL;
	if (!command)
		exit(1);
	while (curr && curr->type != PIPE && \
		curr->type != IN_REDIRECT && curr != OUT_REDIRECT)
	{	
		if (curr->type == CMD)
			command->cmd = curr->data;
		else if (curr->type == FLAG)
			command->flag = curr->data;
		else
			command->target = join_str(command->target, curr->data);
		curr = curr->next;
	}
	parser->command = command;
	add_back_parser(head, parser);
	return (curr);
}

void	parsing_token(t_token *tokens)
{
	t_token		*curr;
	t_parser	*parser;
	t_parser	*head;

	curr = tokens;
	head = NULL;
	while (curr)
	{
		if (curr->type == PIPE)
		{
			parser = pipe_parser(curr);
			add_back_parser(&head, parser);
		}
		else if (curr->type == IN_REDIRECT || curr->type == OUT_REDIRECT)
		{
			parser = redirect_parser(curr, curr->type);
			curr = curr->next;
			add_back_parser(&head, parser);
		}
		else
			curr = command_parser(&head, curr);
		if (!curr)
			curr = curr->next;
	}
}
