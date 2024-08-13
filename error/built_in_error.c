/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:21:13 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/13 18:27:42 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	error_msg_prefix(char *cmd, char *path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
}

int	cd_error(char *cmd, char *path, int errno)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	if (errno == NO_FILE_DIR)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
		return (1);
	}
	if (errno == NOT_SET)
	{	
		ft_putchar_fd(' ', STDERR_FILENO);
		ft_putendl_fd("not set", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	exit_error(char *cmd, char *path, int errno)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (errno == TOO_MANY_ARG)
	{
		ft_putendl_fd(" too many arguments", STDERR_FILENO);
		return (1);
	}
	if (errno == NUMERIC_ARG_REQUIRED)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(" numeric argument required", STDERR_FILENO);
		return (255);
	}
	return (0);
}

int	export_unset_error(char *cmd, char *path, int errno)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errno == NOT_VALID_IDENT)
	{
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd("not a valid identifier", STDERR_FILENO);
		return (1);
	}
	return (0);
}
