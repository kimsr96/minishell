/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:00:10 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/18 17:39:18 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sigint;

void	get_next_command_line(t_block *block, char *str)
{
	unlink_tmpfile(block);
	if (block)
		free_block_all(block);
	add_history(str);
	free(str);
	g_sigint = 0;
	set_terminal_print(OFF);
}

void	start_shell(char *str, t_block *block, t_env_list *env)
{
	while (1)
	{
		str = readline("minishell$ ");
		if (g_sigint)
			update_exit_code(1, env);
		if (!str)
			break ;
		if (parsing_token(&block, env, str))
		{
			get_next_command_line(block, str);
			continue ;
		}
		signal(SIGINT, SIG_IGN);
		if (check_heredoc(block, env))
		{
			get_next_command_line(block, str);
			continue ;
		}
		signal(SIGINT, SIG_IGN);
		exec(block, env);
		signal(SIGINT, handle_sigint);
		get_next_command_line(block, str);
	}
	set_terminal_print(ON);
	printf("\e7\e[A\e[11Cexit\n");
}

void	check_leaks(void)
{
	system("leaks --list -- minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_block		*block;
	t_env_list	*env;

	if (argc != 1)
		return (0);
	if (argv)
		argv = NULL;
	str = NULL;
	block = NULL;
	env = NULL;
	g_sigint = 0;
	set_signal();
	env = get_env(&env, envp);
	start_shell(str, block, env);
	free_env(&env);
	check_leaks();
	return (0);
}
