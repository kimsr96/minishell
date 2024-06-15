/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:00:44 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/15 16:39:26 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	change_value(t_env_list *env, char *key, char *value)
{
	t_env_list	*target;

	target = find_key_node(env, key);
	if (!target)
		return ;
	free(target->value);
	target->value = value;
}

t_env_list	*find_key_node(t_env_list *env, char *find_key)
{
	while (env)
	{
		if (env->key)
			if (!ft_strncmp(env->key, find_key, ft_strlen(env->key)))
				return (env);
		env = env->next;
	}
	return (NULL);
}
