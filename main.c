/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:00:10 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/13 17:02:56 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_block(t_block *block)
{
	int			i;
	t_command	*cmd;
	t_redirect	*curr;

	while (block)
	{
		cmd = block->command;
		if (cmd && (cmd->argv || cmd->redirect))
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
			while (block->command->argv[i])
			{
				if (i == 0)
					printf("cmd: %s\n", block->command->argv[i]);
				else
					printf("argv: %s\n", block->command->argv[i]);
				i++;
			}
		}
		printf("****************************\n");
		block = block->next;
	}
}

void	get_next_command_line(t_block *block, t_token *token, char *str)
{
	unlink_tmpfile(block);
	if (block)
		free_block_all(block);
	if (token)
		free_all_token(token);
	add_history(str);
	free(str);
}

void	start_shell(char *str, t_block *block, t_token *token, t_env_list *env)
{
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
		{
			printf("\e7\e[A\e[11Cexit\n");
			break ;
		}
		if (tokenizer(&token, str, env))
		{
			get_next_command_line(NULL, token, str);
			continue ;
		}
		if (parsing_token(&block, &token, env))
		{
			get_next_command_line(block, token, str);
			continue ;
		}
		signal(SIGINT, SIG_IGN);
		if (check_heredoc(block, env))
		{
			get_next_command_line(block, token, str);
			continue ;
		}
		// printf("%s", block->command->redirect->file_name);
		signal(SIGINT, SIG_IGN);
		if (block)
			exec(block, env);
		signal(SIGINT, signal_handler);
		get_next_command_line(block, token, str);
	}
}

//void check_leaks(void)
//{
//	system("leaks --list -- minishell");
//}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_block		*block;
	t_token		*token;
	t_env_list	*env;

	if (argc != 1)
		return (0);
	if (argv)
		argv = NULL;
	str = NULL;
	block = NULL;
	token = NULL;
	env = NULL;
	set_signal();
	env = get_env(&env, envp);
	start_shell(str, block, token, env);
	free_env(env);
	//check_leaks();
	return (0);
}
