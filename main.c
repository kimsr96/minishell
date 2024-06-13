/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:00:10 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/13 17:03:35 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*init_parser(void)
{
	int			len;
	t_parser	*parser;

	len = 0;
	parser = (t_parser *)malloc(sizeof(parser));
	if (!parser)
		exit(1);
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
		if (parser->command->cmd_path)
			printf("path : %s\n", parser->command->cmd_path);
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
			if (parser)
				execute_cmd(parser);
			free_token(tokens);
			free_parser(parser);
		}
		else
			break ;
		add_history(str);
		free(str);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	if (argc != 1)
		return (0);
	argv = NULL;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	set_signal();
	start_shell();
	return (0);
}
