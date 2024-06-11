/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:47:14 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/11 15:11:32 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../command.h"

void	ft_echo(char *str, int flag, int fd)
{
	if (flag)
		ft_putstr_fd(str, fd);
	else
	{
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
}
