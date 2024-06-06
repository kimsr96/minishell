/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:27:21 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/02 10:41:57 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	quote_len(char *s, char x)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != x)
			len++;
		i++;
	}
	return (len);
}

int	double_quote_exception(char a, char b)
{
	if (a == '\\' && (b == '\\' || b == '$' \
			|| b == '\'' || b == '"'))
		return (1);
	else
		return (0);
}

char	*realloc_without_quote(char *s, char x, size_t len)
{
	int		i;
	char	*r;

	i = 0;
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		exit(1);
	r[len] = '\0';
	len = 0;
	while (s[i])
	{
		if (x == '"' && double_quote_exception(s[i], s[i + 1]))
		{
			i++;
			continue ;
		}
		if (s[i] != x)
		{
			r[len] = s[i];
			len++;
		}
		i++;
	}
	free(s);
	return (r);
}
