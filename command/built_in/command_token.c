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

#include "../command.h"

void	find_cmd2(t_parser *parser)
{
	if (!ft_strncmp(parser->command->cmd, "export", 6))
	{
		parser->type = CMD;
	}
	else if (!ft_strncmp(parser->command->cmd, "unset", 5))
	{
		parser->type = CMD;
	}
	else if (!ft_strncmp(parser->command->cmd, "env", 3))
	{
		parser->type = CMD;
	}
	else
		return ;
}

void	find_cmd(t_parser *parser)
{
	if (!ft_strncmp(parser->command->cmd, "echo", 4))
	{
		parser->type = CMD;
		//ft_echo(parser->command->cmd, 1, 0);
	}
	else if (!ft_strncmp(parser->command->cmd, "cd", 2))
	{
		parser->type = CMD;
		ft_cd(parser->next->command->cmd);
	}
	else if (!ft_strncmp(parser->command->cmd, "pwd", 3))
	{
		parser->type = CMD;
		ft_pwd();
	}
	else if (!ft_strncmp(parser->command->cmd, "exit", 4))
	{
		parser->type = CMD;
		exit(1);
	}
	else
		find_cmd2(parser);
}

int	check_cmd(t_parser *parser)
{
	t_parser	*curr;

	curr = parser;
	while (curr)
	{
		if (curr->command->cmd)
			find_cmd(curr);
		curr = curr->next;
	}
}
