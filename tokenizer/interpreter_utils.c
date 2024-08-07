/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:00:37 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/07 13:19:00 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	split_data(t_token *token, char *s)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	while (s[space] && ft_isspace(s[space]))
		space++;
	while (s[i])
	{
		if (ft_isspace(s[i]))
			break ;
		i++;
	}
	if ((s[i] == '\0' && !space) || token->quote_type != DEFAULT)
	{
		return (0);
	}
	else if (space && token->space)
		return (-1);
	else
		return (1);
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
