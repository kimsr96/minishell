/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:36:17 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/17 21:37:57 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_cmd_error(t_block *block)
{
	int		status;
	char	*cmd_path;

	status = -1;
	cmd_path = block->command->cmd_path;
	if (!cmd_path)
		status = raise_cmd_error(block, COMMAND_NOT_FOUND);
	else if (!is_exist_file(cmd_path))
		status = raise_cmd_error(block, NO_SUCH_FILE_OR_DIR);
	else if (is_directory(cmd_path))
		status = raise_cmd_error(block, IS_A_DIRECTORY);
	else if (!is_executable(cmd_path))
		status = raise_cmd_error(block, PERMISSION_DENIED);
	return (status);
}

int	is_exist_file(char *path)
{
	if (access(path, F_OK) == 0)
		return (1);
	return (0);
}

int	is_executable(char *path)
{
	if (access(path, X_OK) == 0)
		return (1);
	return (0);
}
