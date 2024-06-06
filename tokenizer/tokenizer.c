/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:43:27 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/06 12:14:41 by seungryk         ###   ########.fr       */
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

int	token_len(char *s)
{
	int	len;

	len = 0;
	while (s[len])
	{
		if (is_space(s[len]))
			return (len);
		else if (is_metachar(s[len]))
			return (len + 1);
		len++;
	}
	return (len);
}

void	print_token(t_token	*token)
{
	while (token)
	{
		printf("data : %s\n", token->data);
		printf("type : %d\n", (int)token->type);
		token = token->next;
	}
}

t_token	*tokenizer(char *s)
{
	int			i;
	int			len;
	t_token		*token;
	t_token		*head;

	i = 0;
	head = NULL;
	while (s[i])
	{
		len = token_len(&s[i]);
		if (len == 0)
		{
			i++;
			continue ;
		}
		token = new_token(&s[i], len, 0);
		add_back_token(&head, token);
		i += len;
	}
	parse_quote(head);
	parse_env(head);
	check_cmd(head);
	return (head);
}
