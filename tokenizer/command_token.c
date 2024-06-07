/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:29:24 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/07 15:01:18 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	find_cmd2(t_token *token)
{
	if (!ft_strncmp(token->data, "export", 6))
	{
		token->type = CMD;
	}
	else if (!ft_strncmp(token->data, "unset", 5))
	{
		token->type = CMD;
	}
	else if (!ft_strncmp(token->data, "env", 3))
	{
		token->type = CMD;
	}
	else
		return ;
}

void	find_cmd(t_token *token)
{
	if (!ft_strncmp(token->data, "echo", 4))
	{
		token->type = CMD;
		//ft_echo(token->data, 1, 0);
	}
	else if (!ft_strncmp(token->data, "cd", 2))
	{
		token->type = CMD;
		ft_cd(token->next->data);
	}
	else if (!ft_strncmp(token->data, "pwd", 3))
	{
		token->type = CMD;
		ft_pwd();
	}
	else if (!ft_strncmp(token->data, "exit", 4))
	{
		token->type = CMD;
		exit(1);
	}
	else
		find_cmd2(token);
}

void	check_cmd(t_token *token)
{
	while (token)
	{
		find_cmd(token);
		token = token->next;
	}
}
