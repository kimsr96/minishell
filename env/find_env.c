/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:00:44 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/04 17:03:10 by seungryk         ###   ########.fr       */
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

void	change_add_value(t_env_list *head, char *key, char *value)
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

void	change_value(t_env_list *head, char *key, char *value)
{
	t_env_list	*node;

	node = find_key_node(head, key);
	if (!node)
		return ;
	else
	{
		free(node->value);
		node->value = value;
	}
}

t_env_list	*find_key_node(t_env_list *head, char *find_key)
{
	size_t		key_len;
	t_env_list	*env;

	key_len = ft_strlen(find_key);
	if (key_len == 0)
		return (NULL);
	env = head;
	while (env)
	{
		if (env->key && key_len == ft_strlen(env->key))
			if (!ft_strncmp(env->key, find_key, key_len))
				return (env);
		env = env->next;
	}
	return (NULL);
}
