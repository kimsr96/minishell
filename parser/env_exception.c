/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exception.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:25:39 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/30 13:40:36 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	shift_left(char **str)
{
	int	i;

	i = 0;
	while (str[i + 1])
	{
		free(str[i]);
		str[i] = ft_strdup(str[i + 1]);
		i++;
	}
	str[i] = NULL;
}

void	env_exception(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->target[i + 1])
	{
		if (!ft_strncmp(cmd->target[i], "env", 3))
		{
			if (cmd->target[i + 1] == NULL)
				return ;
			else
				shift_left(cmd->target);
		}
		else
			return ;
	}
}