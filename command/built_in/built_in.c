/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:58:02 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/13 15:09:50 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	is_builtin(t_block *block)
{
	char	*cmd;

	if (*block->command->argv == NULL)
		return (0);
	cmd = *block->command->argv;
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_block *block, t_env_list *env, int has_pipe)
{
	int			status;
	char		*cmd;

	status = 0;
	cmd = *block->command->argv;
	if (ft_strncmp(cmd, "echo", 5) == 0)
		status = ft_echo(block->command->argv, STDOUT_FILENO);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		status = ft_cd(block, env);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		status = ft_pwd();
	if (ft_strncmp(cmd, "exit", 5) == 0)
		status = ft_exit(block->command->argv, has_pipe);
	if (ft_strncmp(cmd, "export", 7) == 0)
		status = ft_export(env, block->command->argv);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		status = ft_unset(env, block->command->argv);
	if (ft_strncmp(cmd, "env", 4) == 0)
		status = ft_env(env, STDOUT_FILENO);
	return (status);
}
