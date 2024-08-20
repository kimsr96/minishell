/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:47:14 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/20 11:53:17 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static void	print_str(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (str[i + 1] == '\\')
			{
				ft_putchar_fd('\\', fd);
				i++;
			}
		}
		else
			ft_putchar_fd(str[i], fd);
		i++;
	}
}

static void	print_echo(char **str, int flag_num, int len, int fd)
{
	int	i;

	i = flag_num + 1;
	if (str == NULL)
		ft_putchar_fd('\n', fd);
	while (str[i])
	{
		print_str(str[i], fd);
		if (len - flag_num > 1 && str[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!flag_num)
		ft_putchar_fd('\n', fd);
}

static int	without_newline(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[++i] == 'n')
	{
		while (str[++i])
		{
			if (str[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

static int	get_flag_num(char **str, int len)
{
	int	i;
	int	first_flag;

	if (len <= 1)
		return (0);
	i = 1;
	first_flag = without_newline(str[i]);
	if (!first_flag)
		return (0);
	while (str[++i])
	{
		if (without_newline(str[i]))
			first_flag++;
		else
			return (first_flag);
	}
	return (first_flag);
}

int	ft_echo(char **str, int fd)
{
	int	len;
	int	flag_num;

	len = 0;
	while (str[len])
		len++;
	flag_num = get_flag_num(str, len);
	print_echo(str, flag_num, len - 1, fd);
	return (0);
}
