/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:46:50 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/04 17:35:32 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	remove_quote(t_token *token, int len)
{
	int		i;
	int		idx;
	char	*ret;

	i = 0;
	idx = 0;
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

int	quote_token(t_token **head)
{
	int		len;
	t_token	*curr;

	curr = *head;
	while (curr)
	{
		curr->quote_type = DEFAULT;
		len = quote_len(curr);
		if (len == -1)
			return (1);
		else
			remove_quote(curr, len);
		curr = curr->next;
	}
	return (0);
}
