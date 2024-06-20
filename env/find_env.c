/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:00:44 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/20 17:12:30 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	add_env_value(t_env_list *head, char *key, char *value)
{
	t_env_list	*node;
	char		*new_value;

	node = find_key_node(head, key);
	if (!node)
	{
		node = new_env_list(key, value);
		add_back_env(&head, node);
	}
	else
	{
		new_value = ft_strjoin(node->value, value);
		free(node->value);
		free(value);
		node->value = new_value;
	}
}

void	change_env_value(t_env_list *head, char *key, char *value)
{
	t_env_list	*node;

	node = find_key_node(head, key);
	if (!node)
	{
		node = new_env_list(key, value);
		add_back_env(&head, node);
	}
	else
	{
		free(node->value);
		node->value = value;
	}
}

t_env_list	*find_key_node(t_env_list *head, char *find_key)
{
	t_env_list	*env;

	env = head;
	while (env)
	{
		if (env->key)
			if (!ft_strncmp(env->key, find_key, ft_strlen(env->key)))
				return (env);
		env = env->next;
	}
	return (NULL);
}
