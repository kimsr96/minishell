/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:43:27 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/30 17:06:29 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

static int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	else
		return (0);
}

static int	is_metachar(char *s)
{
	if (!ft_strncmp(s, ">>", 2) || !ft_strncmp(s, "<<", 2))
		return (2);
	else if (*s == '|' || *s == '>' || *s == '<')
		return (1);
	else
		return (0);
}

int	token_len(char *s, int quote)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if ((is_space(s[i]) && quote == 0) || is_metachar(&s[i]))
			break ;
		else if (i != 0 && (s[i] == '\'' || s[i] == '"'))
		{
			if (quote)
				quote = 0;
			else
				quote = 1;
		}
		len++;
	}
	return (len);
}

void	print_token(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr)
	{
		printf("%s\n", curr->data);
		curr = curr->next;
	}
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
			len = is_metachar(&s[i]);
			if (!len)
				len = token_len(&s[i], is_quote(s[i]));
			token = new_token(&s[i], len, is_quote(s[i]));
			add_back_token(&head, token);
			i += len;
		}
	}
	quote_token(head);
	env_token(head);
	// print_token(head);
	return (head);
}
