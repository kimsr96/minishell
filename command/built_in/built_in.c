/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:58:02 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/07 17:06:26 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	is_builtin(t_block *block)
{
	char	*cmd;

	if (*block->command->target == NULL)
		return (0);
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
	return (0);
}

void	exec_builtin(t_block *block, t_env_list *env)
{
	int			status;
	char		*cmd;
	t_env_list	*target_node;

	status = 0;
	cmd = *block->command->target;
	if (ft_strncmp(cmd, "echo", 4) == 0)
		status = ft_echo(block->command->target, STDOUT_FILENO);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		status = ft_cd(block, env);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		status = ft_pwd();
	if (ft_strncmp(cmd, "exit", 4) == 0)
		status = ft_exit(block->command->target);
	if (ft_strncmp(cmd, "export", 6) == 0)
		status = ft_export(env, block->command->target);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		status = ft_unset(env, block->command->target);
	if (ft_strncmp(cmd, "env", 3) == 0)
		status = ft_env(env, STDOUT_FILENO);
	target_node = find_key_node(env, "?");
	if (target_node)
		target_node->value = ft_itoa(status);
}
