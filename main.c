/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:00:10 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/05 14:36:09 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_t_cmd(t_parser *parser)
{
	parser = (t_parser *)malloc(sizeof(parser));
	ft_memset(parser, 0, sizeof(parser));
}

void	start_shell(char **argv, t_parser *parser)
{
	int			i;
	char		*str;
	t_token	*tokens;

	i = 0;
	argv = NULL;
	parser = NULL;
	while (1)
	{
		str = readline("minishell$ ");
		if (str)
		{
			tokens = tokenizer(str);
			parsing_token(tokens);
			execute_cmd(tokens);
			print_token(tokens);
			free_token(tokens);
		}
		add_history(str);
	}
}

int	main(int argc, char **argv)
{
	t_parser	parser;

	if (argc != 1)
		return (0);
	init_t_cmd(&parser);
	start_shell(argv, &parser);
	free(&parser);
	return (0);
}
