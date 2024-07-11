/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:47:14 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/11 14:58:52 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static void	print_echo(char **str, int flag, int fd)
{
	int	i;

	if (flag)
		i = 2;
	else
		i = 1;
	if (str == NULL)
		ft_putchar_fd('\n', fd);
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', fd);
}

static int	is_flag(char **str, int len)
{
	int		i;
	char	*flag;

	i = 0;
	if (len <= 1)
		return (0);
	flag = str[1];
	if (flag[i] != '-')
		return (0);
	while (flag[++i])
	{
		if (flag[i] != 'n')
			return (0);
	}
	return (1);
}

void	ft_echo(char **str, int fd)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	if (is_flag(str, len))
		print_echo(str, 1, fd);
	else
		print_echo(str, 0, fd);
}
