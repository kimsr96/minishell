/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:19:11 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/17 21:28:53 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	get_env_list_size(t_env_list *env)
{
	int	size;

	size = 0;
	env = env->next;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

static char	*join_env(t_env_list *env)
{
	int		key_len;
	int		value_len;
	int		str_len;
	char	*ret;

	key_len = ft_strlen(env->key);
	if (env->value)
		value_len = ft_strlen(env->value);
	else
		value_len = 0;
	str_len = key_len + value_len + 2;
	ret = ft_calloc(str_len, sizeof(char));
	ft_strlcpy(ret, env->key, str_len);
	if (env->value)
	{
		ft_strlcat(ret, "=", str_len);
		ft_strlcat(ret, env->value, str_len);
	}
	return (ret);
}

char	**get_envp(t_env_list *env)
{
	char	**envp;
	int		idx;

	envp = ft_calloc(get_env_list_size(env) + 1, sizeof(char *));
	idx = 0;
	env = env->next;
	while (env)
	{
		envp[idx] = join_env(env);
		idx++;
		env = env->next;
	}
	return (envp);
}
