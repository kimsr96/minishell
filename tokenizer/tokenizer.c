/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:43:27 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/20 12:25:35 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_metachar(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == ';')
		return (1);
	else
		return (0);
}

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

//int	token_len(char *s)
//{
//	int	len;

//	len = 0;
//	while (s[len])
//	{
//		if (is_quote(s[len]))
			
//		if (is_metachar(s[len]))
//			return (len + 1);
//		if (is_space(s[len]))
//			return (len);
//		len++;
//	}
//	return (len);
//}

//t_token	*tokenizer(char *s)
//{
//	int			i;
//	int			len;
//	t_token		*token;
//	t_token		*head;

//	i = 0;
//	head = NULL;
//	while (s[i])
//	{
//		len = token_len(&s[i]);
//		if (len == 0)
//		{
//			i++;
//			continue ;
//		}
//		token = new_token(&s[i], len, 0);
//		add_back_token(&head, token);
//		i += len;
//	}
//	quote_token(head);
//	env_token(head);
//	return (head);
//}

static int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	else
		return (0);
}

int	token_len(char *s, int quote)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (is_space(s[i]) && quote == 0)
			break ;
		else if (i != 0 && (s[i] == '\'' || s[i] == '"'))
		{
			if (quote)
				quote = 0;
			else
				quote = 1;
		}
		i++;
		len++;
	}
	return (len);
}

t_token	*tokenizer(char *s)
{
	int		i;
	int		len;
	t_token	*token;
	t_token	*head;

	i = 0;
	head = NULL;
	while (s[i])
	{
		if (is_space(s[i]))
			i++;
		else
		{
			len = token_len(&s[i], is_quote(s[i]));
			token = new_token(&s[i], len, is_quote(s[i]));
			add_back_token(&head, token);
			i += len;
		}
	}
	quote_token(head);
	env_token(head);
	return (head);
}
