/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:39:03 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/01 18:46:39 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_env(t_env_list *env, int fd)
{
	t_env_list	*curr;

	curr = env->next;
	while (curr)
	{
		ft_putstr_fd(curr->key, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(curr->value, fd);
		ft_putchar_fd('\n', fd);
		curr = curr->next;
	}
	return (0);
}
