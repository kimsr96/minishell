/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:00:10 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/07 14:56:24 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*init_parser(void)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(parser));
	ft_memset(parser, 0, sizeof(parser));
	return (parser);
}

void	print_parser(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser)
	{
		//printf("%d\n", parser->type);
		if (parser->command->target)
		{
			while (parser->command->target[i])
			{
				printf("%s \n", parser->command->target[i]);
				i++;
			}
			printf("\n");
		}
		parser = parser->next;
	}
}

void	start_shell(void)
{
	char		*str;
	t_token		*tokens;
	t_parser	*parser;

	while (1)
	{
		str = readline("minishell$ ");
		if (str)
		{
			parser = init_parser();
			tokens = tokenizer(str);
			parsing_token(&parser, tokens);
			print_parser(parser);
			//execute_cmd(tokens);
			//print_token(tokens);
			free_token(tokens);
			free_parser(parser);
		}
		add_history(str);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 1)
		return (0);
	argv = NULL;
	start_shell();
	return (0);
}
