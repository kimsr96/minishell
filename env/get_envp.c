/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:19:11 by hyeonble          #+#    #+#             */
/*   Updated: 2024/07/05 18:37:08 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	get_env_list_size(t_env_list *env)
{
	int	size;

	size = 0;
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
	value_len = ft_strlen(env->value);
	str_len = key_len + value_len + 2;
	ret = ft_calloc(str_len, sizeof(char));
	ft_strlcpy(ret, env->key, str_len);
	ft_strlcat(ret, "=", str_len);
	ft_strlcat(ret, env->value, str_len);
	return (ret);
}

char	**get_envp(t_env_list *env)
{
	char	**envp;
	int		idx;

	envp = ft_calloc(get_env_list_size(env) + 1, sizeof(char *));
	idx = 0;
	while (env)
	{
		envp[idx] = join_env(env);
		env = env->next;
	}
	return (envp);
}
