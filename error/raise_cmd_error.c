/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raise_cmd_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:52:32 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/13 13:58:28 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	raise_cmd_error(t_block *block, int errno)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(block->command->argv[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errno == COMMAND_NOT_FOUND)
	{
		ft_putendl_fd("command not found", STDERR_FILENO);
		return (127);
	}
	if (errno == NO_SUCH_FILE_OR_DIR)
	{
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
		return (127);
	}
	if (errno == IS_A_DIRECTORY)
	{
		ft_putendl_fd("is a directory", STDERR_FILENO);
		return (126);
	}
	if (errno == PERMISSION_DENIED)
	{
		ft_putendl_fd("Permission denied", STDERR_FILENO);
		return (126);
	}
	return (0);
}
