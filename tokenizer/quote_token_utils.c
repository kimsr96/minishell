/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:27:21 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/05 20:31:35 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

//int	quote_len(t_token *token)
//{
//	size_t	i;
//	size_t	len;

//	i = 0;
//	len = 0;
//	while (token->data[i])
//	{
//		if (get_quote_type(token, token->data[i]))
//			len++;
//		i++;
//	}
//	if (token->quote_type)
//	{
//		perror("quote error");
//		return (-1);
//	}
//	return (len);
//}

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

int	double_quote_exception(char a, char b)
{
	if (a == '\\' && (b == '\\' || b == '$' \
			|| b == '\'' || b == '"'))
		return (1);
	else
		return (0);
}
