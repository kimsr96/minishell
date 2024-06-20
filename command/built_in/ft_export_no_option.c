/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_option.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:53:38 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/20 16:54:19 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include <stdio.h>

size_t	get_min_len(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 < len_s2)
		return (len_s1);
	else
		return (len_s2);
}

void	sort_env(t_env_list *head)
{
	size_t		min_len;
	t_env_list	*curr;
	t_env_list	*next_node;
	char		*temp[2];

	curr = head;
	while (curr->next)
	{
		next_node = curr->next;
		while (next_node)
		{
			min_len = get_min_len(curr->key, next_node->key);
			if (ft_strncmp(curr->key, next_node->key, min_len) > 0)
			{
				temp[0] = curr->key;
				temp[1] = curr->value;
				curr->key = next_node->key;
				curr->value = next_node->value;
				next_node->key = temp[0];
				next_node->value = temp[1];
			}
			next_node = next_node->next;
		}
		curr = curr->next;
	}
}

void	sort_print_env(t_env_list *head)
{
	sort_env(head);
	while (head)
	{
		printf("declare -x %s=\"%s\"\n", head->key, head->value);
		head = head->next;
	}
}
