/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:51:51 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/30 21:51:56 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../command.h"
#include "exec.h"

int	is_directory(char *filename)
{
	int	fd;

	fd = open(filename, O_DIRECTORY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	raise_file_error(char *filename, char *error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	return (-1);
}

int check_file(t_redirect *redirection)
// 경우의 수
// 1. infile이 존재하지 않을때
// 2. file이 directory일때
// 3. infile이 존재하지만, 권한이 없을때
// 4. outfile이 존재하지만, 권한이 없을때
// 문제있으면 -1 return, 아니면 0 return.
{
	char	*filename;
	int		type;

	filename = redirection->file_name;
	type = redirection->io_type;
	if (is_directory(filename))
		raise_file_error(filename, "Is a directory\n");
	if (type == IN_REDIRECT)
	{
		if (access(filename, F_OK) != 0)
			return (raise_file_error(filename, "No such file or directory\n"));
		if (access(filename, R_OK) != 0)
			return (raise_file_error(filename, "Permission denied\n"));
	}
	if (type == OUT_REDIRECT || type == APPEND_REDIRECT)
	{
		if (access(filename, F_OK) == 0 && access(filename, W_OK) != 0)
			return (raise_file_error(filename, "Permission denied\n"));
	}
	return (0);
}
int	open_file(t_redirect *redirection)
{
	int		fd;
	char	*filename;

	if (check_file(redirection) < 0)
		return (-1);
	fd = -1;
	filename = redirection->file_name;
	if (redirection->io_type >= IN_REDIRECT && redirection->io_type <= APPEND_REDIRECT)
	{
		if (redirection->io_type == IN_REDIRECT)
			fd = open(filename, O_RDONLY);
		else if (redirection->io_type == HEREDOC_REDIRECT)
			fd = open(filename, O_RDONLY);
		else if (redirection->io_type == OUT_REDIRECT)
			fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	if (fd < 0)
	{
		ft_putstr_fd("file open error\n", 2);
		return (-1);
	}
	return (fd);
}

int	redirect(t_block *block)
{
	int	fd;

	if (block == NULL || block->redirection == NULL)
	{
		printf("%d", block->type);
		return (-1);
	}
	fd = open_file(block->redirection);
	if (fd < 0)
		return (-1);
	if (block->type == IN_REDIRECT || block->type == HEREDOC_REDIRECT)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	return (1);
}
