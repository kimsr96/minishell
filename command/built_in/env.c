/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:39:03 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/13 16:55:43 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	ft_env(char **envp, int fd)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		path = getenv(envp[i]);
		ft_putstr_fd(path, fd);
		ft_putchar_fd('\n', fd);
	}
}
