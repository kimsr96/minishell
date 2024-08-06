/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:18:35 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/06 15:12:50 by seungryk         ###   ########.fr       */
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

int	get_env_len(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '?')
		return (1);
	while (s[i])
	{
		if (ft_isspace(s[i]) || ft_isquote(s[i]) || s[i] == '$')
			break ;
		i++;
	}
	return (i);
}

char	*get_env_var_name(char *s, int len)
{
	int		i;
	int		j;
	char	*env_s;

	i = 0;
	j = 0;
	env_s = malloc(sizeof(char) * (len + 1));
	if (!env_s)
		return (NULL);
	env_s[len] = '\0';
	while (s[i] && i < len)
	{
		if (s[i] != '\'' && s[i] != '"')
			env_s[j++] = s[i];
		i++;
	}
	return (env_s);
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
