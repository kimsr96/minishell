/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:11:13 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/13 15:10:05 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	check_digit(char *s)
{
	int	i;
	int	len;
	int	flag;

	i = -1;
	len = 0;
	flag = 0;
	while (s[++i])
	{
		if (ft_isspace(s[i]))
			continue ;
		if (ft_isdigit(s[i]))
		{
			flag = 1;
			len++;
		}
		else if (s[i] == '-' && flag)
			return (-1);
		else if (s[i] != '-' && !ft_isdigit(s[i]))
			return (-1);
	}
	if (len)
		return (len);
	else
		return (-1);
}

long long	ft_atol(const char *str, int *error)
{
	long long			num;
	long long			temp;
	int					idx;
	int					sign;

	num = 0;
	idx = 0;
	sign = 1;
	while ((str[idx] >= 9 && str[idx] <= 13) || str[idx] == 32)
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
	{
		if (str[idx++] == '-')
			sign *= -1;
	}
	while (str[idx] && (str[idx] >= '0' && str[idx] <= '9'))
	{
		if ((sign == 1 && (num > (LLONG_MAX - (str[idx] - '0')) / 10)) || \
			(sign == -1 && (-num < (LLONG_MIN + (str[idx] - '0')) / 10)))
			*error = 1;
		temp = num * 10 + (str[idx] - '0');
		num = temp;
		idx++;
	}
	return (num * sign);
}

unsigned long long	within_range(char *argv)
{
	unsigned long long	num;
	int					error;

	error = 0;
	num = ft_atol(argv, &error);
	if (error)
		exit_error("exit", argv, NUMERIC_ARG_REQUIRED);
	while (num % 256 >= 256)
		num /= 256;
	return (num % 256);
}

int	ft_exit(char **argv, int has_pipe)
{
	int					i;
	unsigned long long	exit_num;

	i = 0;
	exit_num = 0;
	if (!has_pipe)
		printf("exit\n");
	while (argv[i])
		i++;
	if (argv[1])
	{
		if (check_digit(argv[1]) == -1)
			exit_error("exit", argv[1], NUMERIC_ARG_REQUIRED);
		else if (i > 2)
			exit_error("exit", argv[1], TOO_MANY_ARG);
		else
			exit_num = within_range(argv[1]);
	}
	exit(exit_num);
	return (exit_num);
}
