/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:00:37 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/06 15:10:08 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	split_data(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	join_env_str(t_token *token, char *ret, int j, char **value_set)
{
	int		i;
	int		len;
	t_token	*n_token;

	i = 0;
	len = 0;
	while (value_set[i][len])
	{
		ret[j++] = value_set[i][len];
		len++;
	}
	while (value_set[++i])
	{
		n_token = new_token(value_set[i], ft_strlen(value_set[i]));
		n_token->next = token->next;
		token->next = n_token;
		token = n_token;
	}
	value_set = free_str(value_set);
	return (len);
}
