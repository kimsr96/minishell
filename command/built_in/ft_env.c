/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:39:03 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/01 15:11:53 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_env(t_env_list *env, int fd)
{
	while (env)
	{
		ft_putstr_fd(env->key, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(env->value, fd);
		ft_putchar_fd('\n', fd);
		env = env->next;
	}
	return (0);
}
