/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:00:10 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/20 12:18:39 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parser(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser)
	{
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

void	start_shell(t_env_list *env)
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
				execute_cmd(parser, env);
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
	int			i;
	t_env_list	*env;

	i = 0;
	if (argc != 1)
		return (0);
	argv = NULL;
	env = NULL;
	set_signal();
	env = get_env(env, envp);
	start_shell(env);
	free_env(env);
	return (0);
}
