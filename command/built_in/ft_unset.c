/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:09:47 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/12 16:53:25 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	*free_node(t_env_list *target)
{
	free(target->key);
	free(target->value);
	free(target);
	return (NULL);
}

void	connect_node(t_env_list *curr, t_env_list *target)
{
	while (curr)
	{
		if (curr->next == target)
		{
			curr->next = target->next;
			break ;
		}
		curr = curr->next;
	}
}

int	ft_unset(t_env_list *head, char **str)
{
	int			i;
	t_env_list	*curr;
	t_env_list	*target;

	i = 0;
	while (str[++i])
	{
		curr = head;
		if (check_key_name(str[i]))
			return (export_unset_error("unset", str[i], NOT_VALID_IDENT));
		target = find_key_node(head, str[i]);
		if (target)
		{
			connect_node(curr, target);
			target = free_node(target);
		}
	}
	return (0);
}
