/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:08:01 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/24 14:54:13 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	get_quote_type(t_token *token, char c)
{
	if (token->quote_type == S_QUOTE)
	{
		if (c == '\'')
			token->quote_type = DEFAULT;
		else
			return (S_QUOTE);
	}
	else if (token->quote_type == D_QUOTE)
	{
		if (c == '"')
			token->quote_type = DEFAULT;
		else
			return (D_QUOTE);
	}
	else
	{
		if (c == '"')
			token->quote_type = D_QUOTE;
		else if (c == '\'')
			token->quote_type = S_QUOTE;
		else
			return (3);
	}
	return (0);
}

int	valid_quote(t_token **t_head, t_env_list *env)
{
	int		i;
	t_token	*curr;

	i = 0;
	curr = *t_head;
	while (curr)
	{
		i = 0;
		while (curr->data[i])
		{
			get_quote_type(curr, curr->data[i]);
			i++;
		}
		if (curr->quote_type)
			return (parsing_error(env, ERR_SYNTAX, 258));
		curr = curr->next;
	}
	return (0);
}
