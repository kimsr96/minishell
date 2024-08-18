/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exception.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:25:39 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/18 16:34:31 by seungryk         ###   ########.fr       */
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

//int	env_exception(t_command *cmd)
//{
//	int	i;

//	i = 0;
//	if (!cmd->argv)
//		return (0);
//	if (!ft_strncmp(cmd->argv[i], "env", 3))
//	{
//		while (cmd->argv[i])
//			i++;
//	}
//	if (i > 1)
//		return (1);
//}
