/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raise_file_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:18:40 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/13 16:38:50 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	raise_file_error(char *filename, int errno)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errno == IS_A_DIRECTORY)
	{
		ft_putendl_fd("is a directory", STDERR_FILENO);
		return (-1);
	}
	if (errno == NO_SUCH_FILE_OR_DIR)
	{
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
		return (-1);
	}
	if (errno == PERMISSION_DENIED)
	{
		ft_putendl_fd("Permission denied", STDERR_FILENO);
		return (-1);
	}
	return (0);
}
