/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:29:24 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/11 15:14:05 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	find_cmd2(t_parser *parser, char *cmd)
{
	(void)parser;
	if (!ft_strncmp(cmd, "export", 6))
	{
		//ft_export();
		return (1);
	}
	else if (!ft_strncmp(cmd, "unset", 5))
	{
		//ft_unset();
		return (1);
	}
	else if (!ft_strncmp(cmd, "env", 3))
	{
		ft_env(parser->envp, STDOUT_FILENO);
		return (1);
	}
	else
		return (0);
}

static int	find_cmd(t_parser *parser, char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
	{
		ft_echo(parser->command->target, STDOUT_FILENO);
		return (1);
	}
	else if (!ft_strncmp(cmd, "cd", 2))
	{
		ft_cd(parser);
		return (1);
	}
	else if (!ft_strncmp(cmd, "pwd", 3))
	{
		ft_pwd();
		return (1);
	}
	else if (!ft_strncmp(cmd, "exit", 4))
	{
		ft_exit();
		return (1);
	}
	else
		return (find_cmd2(parser, cmd));
}

int	check_cmd(t_parser *parser)
{
	t_parser	*curr;

	curr = parser;
	while (curr)
	{
		if (*curr->command->target)
			if (find_cmd(parser, *curr->command->target))
				return (1);
		curr = curr->next;
	}
	return (0);
}

