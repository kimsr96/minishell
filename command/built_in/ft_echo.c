/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:47:14 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/11 17:02:37 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static void	print_echo(char **str, int flag_num, int len, int fd)
{
	int	i;

	i = flag_num + 1;
	if (str == NULL)
		ft_putchar_fd('\n', fd);
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		if (len - flag_num > 1)
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!flag_num)
		ft_putchar_fd('\n', fd);
}

static int	check_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		while (str[++i])
		{
			if (str[i] != 'n')
				return (0);
		}
		return (1);
	}
	else
		return (0);
}

static int	get_flag_num(char **str, int len)
{
	int		idx;
	int		flag_num;

	idx = 1;
	flag_num = 0;
	if (len <= 1)
		return (0);
	while (str[idx])
	{
		if (check_flag(str[idx]))
			flag_num++;
		idx++;
	}
	return (flag_num);
}

void	ft_echo(char **str, int fd)
{
	int	len;
	int	flag_num;

	len = 0;
	while (str[len])
		len++;
	flag_num = get_flag_num(str, len);
	print_echo(str, flag_num, len - 1, fd);
}
