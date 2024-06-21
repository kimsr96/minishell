/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_option.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:53:38 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/21 13:43:52 by seungryk         ###   ########.fr       */
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

t_env_list	*copy_env(t_env_list *head)
{
	t_env_list	*curr;
	t_env_list	*new_head;
	t_env_list	*new_node;

	if (!head)
		return (NULL);
	curr = head;
	new_head = NULL;
	new_node = NULL;
	while (curr)
	{
		new_node = new_env_list(curr->key, curr->value);
		if (!new_head)
			new_head = new_node;
		else
			add_back_env(&new_head, new_node);
		curr = curr->next;
	}
	return (new_head);
}

void	sort_print_env(t_env_list *head)
{
	t_env_list	*new_head;

	new_head = copy_env(head);
	sort_env(new_head);
	while (new_head)
	{
		printf("declare -x %s=\"%s\"\n", new_head->key, new_head->value);
		new_head = new_head->next;
	}
	free_env(new_head);
}
