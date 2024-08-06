/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:00:10 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/06 12:52:09 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_block(t_block *block)
{
	int			i;
	t_command 	*cmd;
	t_redirect	*curr;

	while (block)
	{
		cmd = block->command;
		if (cmd && (cmd->target || cmd->redirect))
		{
			curr = cmd->redirect;
			while (curr)
			{
				printf("======REDIRECTION======\n");
				printf("type: %d\n", curr->io_type);
				printf("file_name: %s\n", curr->file_name);
				printf("delimiter: %s\n", curr->delimiter);
				printf("========================\n");
				curr = curr->next;
			}
			i = 0;
			while (block->command->target[i])
			{
				if (i == 0)
					printf("cmd: %s\n", block->command->target[i]);
				else
					printf("target: %s\n", block->command->target[i]);
				i++;
			}
		}
		printf("****************************\n");
		block = block->next;
	}
}

void	get_next_command_line(t_block *block, t_token *token, char *str)
{
	if (token)
		free_all_token(token);
	if (block)
		free_block_all(block);
	add_history(str);
	free(str);
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
		if (tokenizer(&tokens, str, env))
		{
			get_next_command_line(NULL, tokens, str);
			continue ;
		}
		if (parsing_token(&block, tokens, env))
		{
			get_next_command_line(block, tokens, str);
			continue ;
		}
		print_block(block);
		if (block)
			exec(block, env);
		get_next_command_line(block, tokens, str);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env_list	*env;

	if (argc != 1)
		return (0);
	if (argv)
		argv = NULL;
	set_signal();
	env = get_env(&env, envp);
	start_shell(env);
	free_env(env);
	return (0);
}
