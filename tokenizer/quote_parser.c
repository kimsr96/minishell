/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:46:50 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/05 14:36:09 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	double_quote(t_token *token, char *s)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = quote_len(s, '"');
	if (len == ft_strlen(s))
		return ;
	while (i < len)
	{
		if (double_quote_exception(s[i], s[i + 1]))
			len--;
		i++;
	}
	token->data = realloc_without_quote(s, '"', len);
	token->type = QUOTED_WORD;
}

void	single_quote(t_token *token, char *s)
{
	size_t	len;

	len = quote_len(s, '\'');
	if (len == ft_strlen(s))
		return ;
	token->data = realloc_without_quote(s, '\'', len);
	token->type = QUOTED_WORD;
}

void	parse_quote(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		single_quote(curr, curr->data);
		double_quote(curr, curr->data);
		curr = curr->next;
	}
}
