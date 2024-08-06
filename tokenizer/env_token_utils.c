/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:59:51 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/05 20:07:49 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	ft_isquote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	else
		return (0);
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

char	*alloc_ret_str(size_t s_len)
{
	char	*ret;

	ret = malloc(sizeof(char) * (s_len + 1));
	if (!ret)
		exit(1);
	ret[s_len] = '\0';
	return (ret);
}
