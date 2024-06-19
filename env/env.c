/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:51:01 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/19 14:17:10 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	get_key_len(char *envp)
{
	int	len;

	len = 0;
	while (envp[len])
	{
		if (envp[len] == '=')
			break ;
		len++;
	}
	return (len);
}

char	*get_key(char *envp, int len)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_calloc(len + 1, sizeof(char));
	if (!key)
		exit(1);
	while (i < len)
	{
		key[i] = envp[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_value(char *envp, int len)
{
	int		i;
	char	*value;

	i = 0;
	value = ft_calloc(len + 1, sizeof(char));
	if (!value)
		exit(1);
	while (*envp)
	{
		if (*envp == '=')
		{
			envp++;
			break ;
		}
		envp++;
	}
	while (i < len && *envp)
	{
		value[i] = *envp;
		i++;
		envp++;
	}
	value[i] = '\0';
	return (value);
}

t_env_list	*get_env(t_env_list *head, char **envp)
{
	int			key_len;
	int			value_len;
	t_env_list	*new_env;

	head = NULL;
	while (*envp)
	{
		key_len = get_key_len(*envp);
		value_len = ft_strlen(*envp) - (key_len + 1);
		new_env = new_env_list(get_key(*envp, key_len), \
						get_value(*envp, value_len));
		add_back_env(&head, new_env);
		envp++;
	}
	return (head);
}
