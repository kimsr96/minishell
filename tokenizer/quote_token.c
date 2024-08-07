/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:08:01 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/07 14:15:45 by seungryk         ###   ########.fr       */
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

int	quote_len(t_token *token)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (token->data[i])
	{
		if (get_quote_type(token, token->data[i]))
			len++;
		i++;
	}
	if (token->quote_type)
	{
		perror("quote error2");
		return (-1);
	}
	return (len);
}

int	valid_quote(t_token *token)
{
	int	i;

	i = 0;
	while (token->data[i])
	{
		get_quote_type(token, token->data[i]);
		i++;
	}
	if (token->quote_type)
	{
		perror("quote error1");
		return (1);
	}
	return (0);
}

void	remove_quote(t_token *token, int len)
{
	int		i;
	int		idx;
	char	*ret;

	i = 0;
	idx = 0;
	if (token->quote_in_env)
		return ;
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
