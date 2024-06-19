/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:09:47 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/19 14:25:51 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	ft_unset(t_env_list *head, char **str)
{
	int			i;
	t_env_list	*curr;
	t_env_list	*target_node;

	i = 1;
	while (str[i])
	{
		curr = head;
		target_node = find_key_node(head, str[i]);
		while (curr)
		{
			if (curr->next == target_node)
			{
				curr->next = target_node->next;
				break ;
			}
			curr = curr->next;
		}
		free(target_node->key);
		free(target_node->value);
		free(target_node);
		i++;
	}
}
