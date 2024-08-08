/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:11:13 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/08 18:51:19 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	check_digit(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
		{
			i++;
			continue ;
		}
		if (ft_isdigit(s[i]))
			flag = 1;
		else if (s[i] == '-' && flag)
			return (1);
		else if (s[i] != '-' && !ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
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

unsigned long long	within_range(char *target)
{
	long long 	num;
	int 		error;

	error = 0;
	num = ft_atol(target, &error);
	if (error)
	{
		perror("numeric argument required");
		num = 255;
	}
	while (num % 256 >= 256)
		num /= 256;
	return(num % 256);
}

int	ft_exit(char **target)
{
	int					i;
	unsigned long long	exit_num;

	i = 0;
	printf("exit\n");
	while (target[i])
		i++;
	if (i > 2)
	{
		exit_num = 0;
		perror("too many arguments");
	}
	if (check_digit(target[1]))
	{
		exit_num = 255;
		perror("numeric argument required");
	}
	exit_num = within_range(target[1]);
	printf("%lld\n", exit_num);
	return (exit_num);
}
