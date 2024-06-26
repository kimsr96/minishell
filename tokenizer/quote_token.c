/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:46:50 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/19 16:03:29 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	is_quote_token(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static void	remove_quote(t_token *token)
{
	int		i;
	int		idx;
	int		len;
	char	*ret;

	i = 0;
	idx = 0;
	len = quote_len(token);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		exit(1);
	ret[len] = '\0';
	while (token->data[i])
	{
		if (get_quote_type(token, token->data[i]))
			ret[idx++] = token->data[i];
		i++;
	}
	free(token->data);
	token->data = ret;
}

void	quote_token(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		curr->quote_type = DEFAULT;
		if (is_quote_token(curr->data))
			remove_quote(curr);
		curr = curr->next;
	}
}
