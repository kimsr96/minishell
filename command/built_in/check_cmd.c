/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:34:51 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/26 22:19:22 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	find_cmd2(t_block *parser, char *cmd, t_env_list *env)
{
	if (!ft_strncmp(cmd, "export", 6))
	{
		ft_export(env, parser->command->target);
		return (1);
	}
	else if (!ft_strncmp(cmd, "unset", 5))
	{
		ft_unset(env, parser->command->target);
		return (1);
	}
	else if (!ft_strncmp(cmd, "env", 3))
	{
		ft_env(env, STDOUT_FILENO);
		return (1);
	}
	else if (!ft_strncmp(cmd, "$?", 2))
	{
		ft_exit_status();
		return (1);
	}
	else
		return (0);
}

static int	find_cmd(t_block *parser, char *cmd, t_env_list *env)
{
	if (!ft_strncmp(cmd, "echo", 4))
	{
		ft_echo(parser->command->target, STDOUT_FILENO);
		return (1);
	}
	else if (!ft_strncmp(cmd, "cd", 2))
	{
		ft_cd(parser, env);
		return (1);
	}
	else if (!ft_strncmp(cmd, "pwd", 3))
	{
		ft_pwd(0);
		return (1);
	}
	else if (!ft_strncmp(cmd, "exit", 4))
	{
		ft_exit();
		return (1);
	}
	else
		return (find_cmd2(parser, cmd, env));
}

int	check_cmd(t_block *parser, t_env_list *env)
{
	t_block	*curr;

	curr = parser;
	while (curr)
	{
		if (curr->type == IN_REDIRECT || curr->type == OUT_REDIRECT || \
				curr->type == HEREDOC_REDIRECT || curr->type == APPEND_REDIRECT)
			return (1);
		else if (curr->command)
		{
			if (*curr->command->target)
			{
				if (find_cmd(parser, *curr->command->target, env))
				{
					g_status = 0;
					return (1);
				}
			}
		}
		curr = curr->next;
	}
	return (0);
}
