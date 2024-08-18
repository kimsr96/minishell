/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:43:27 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/18 16:06:24 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	is_metachar(char *s)
{
	if (!ft_strncmp(s, ">>", 2) || !ft_strncmp(s, "<<", 2))
		return (2);
	else if (*s == '|' || *s == '>' || *s == '<')
		return (1);
	else
		return (0);
}

int	get_quote_type_c(char c, int quote)
{
	if (quote == 1)
	{
		if (c == '\'')
			quote = 0;
		else
			quote = 1;
	}
	else if (quote == 2)
	{
		if (c == '"')
			quote = 0;
		else
			quote = 2;
	}
	else
	{
		if (c == '\'')
			quote = 1;
		else if (c == '"')
			quote = 2;
		else
			quote = 0;
	}
	return (quote);
}

int	token_len(char *s)
{
	int	i;
	int	len;
	int	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (s[i])
	{
		quote = get_quote_type_c(s[i], quote);
		if (quote == 0 && (ft_isspace(s[i]) || is_metachar(&s[i])))
			break ;
		len++;
		i++;
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

int	tokenizer(t_token **head, char *s, t_env_list *env)
{
	int		i;
	int		len;
	t_token	*token;

	i = 0;
	*head = NULL;
	while (s[i])
	{
		if (ft_isspace(s[i]))
			i++;
		else
		{
			len = is_metachar(&s[i]);
			if (!len)
				len = token_len(&s[i]);
			token = new_token(&s[i], len);
			add_back_token(head, token);
			i += len;
		}
	}
	if (token_interpreter(head, env))
		return (1);
	return (0);
}
