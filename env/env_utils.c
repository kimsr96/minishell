/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:18:35 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/03 13:28:28 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	free_env(t_env_list	*env)
{
	t_env_list	*env_next;

	while (env)
	{
		env_next = env->next;
		free(env->key);
		free(env->value);
		env = env_next;
	}
}

void	add_back_env(t_env_list **head, t_env_list *new)
{
	t_env_list	*curr;

	curr = *head;
	if (!curr)
		*head = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

t_env_list	*new_env_list(char *key, char *value)
{
	t_env_list	*new_env;

	new_env = ft_calloc(1, sizeof(t_env_list));
	if (!new_env)
		exit(1);
	new_env->key = key;
	new_env->value = value;
	new_env->next = NULL;
	return (new_env);
}
