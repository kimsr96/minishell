/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:59:51 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/03 15:02:12 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	get_env_len(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			len++;
		i++;
	}
	return (len);
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
