/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:58:02 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/01 15:29:13 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	is_builtin(t_block *block)
{
	char	*cmd;

	cmd = *block->command->target;
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "$?", 2) == 0)
		return (1);
	return (0);
}

void	exec_builtin(t_block *block, t_env_list *env)
{
	char	*cmd;

	cmd = *block->command->target;
	if (ft_strncmp(cmd, "echo", 4) == 0)
		ft_echo(block->command->target, STDOUT_FILENO);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		ft_cd(block, env);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		ft_pwd();
	if (ft_strncmp(cmd, "exit", 4) == 0)
		ft_exit();
	if (ft_strncmp(cmd, "export", 6) == 0)
		ft_export(env, block->command->target);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		ft_unset(env, block->command->target);
	if (ft_strncmp(cmd, "env", 3) == 0)
		ft_env(env, STDOUT_FILENO);
	if (ft_strncmp(cmd, "$?", 2) == 0)
		ft_exit_status();
}
