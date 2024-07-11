/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:00:10 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/11 14:56:08 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_block(t_block *block)
{
	int	i;

	while (block)
	{
		printf("type: %d\n", block->type);
		if (block->type >= 2 && block->type <= 5)
			printf("data: %s\n", block->redirection->file_name);
		else if (block->command && block->command->target)
		{
			i = 0;
			while (block->command->target[i])
			{
				printf("data: %s\n", block->command->target[i]);
				i++;
			}
		}
		block = block->next;
	}
}

void	start_shell(t_env_list *env)
{
	char		*str;
	t_token		*tokens;
	t_block		*block;

	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
		{
			printf("\e7\e[A\e[11Cexit\n");
			break ;
		}
		block = init_block();
		tokens = tokenizer(str);
		parsing_token(&block, tokens, env);
		//print_block(block);
		if (block)
			exec(block, env);
		free_token(tokens);
		free_block_all(block);
		add_history(str);
		free(str);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env_list	*env;

	if (argc != 1)
		return (0);
	if (argv)
		argv = NULL;
	env = NULL;
	set_signal();
	env = get_env(env, envp);
	start_shell(env);
	free_env(env);
	return (0);
}
