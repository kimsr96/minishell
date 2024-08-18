/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:18:35 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/18 18:07:19 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

void	free_env(t_env_list	**head)
{
	t_env_list	*curr;
	t_env_list	*env_next;

	curr = *head;
	while (curr)
	{
		env_next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = env_next;
	}	
}

int	get_env_len(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '?' || ft_isdigit(s[i]))
		return (1);
	while (s[i])
	{
		if (ft_isspace(s[i]) || ft_isquote(s[i]) || s[i] == '$' || s[i] == '=')
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
