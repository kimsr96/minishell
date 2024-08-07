/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:12:22 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/07 13:09:51 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_env_list	*get_target(t_env_list *env, char *s)
{
	int			env_len;
	char		*find_key;
	t_env_list	*target;

	env_len = get_env_len(s);
	find_key = get_env_var_name(s, env_len);
	target = find_key_node(env, find_key);
	free(find_key);
	return (target);
}

static int	interprete_str_len(t_token *token, char *s, t_env_list *env)
{
	int			i;
	int			len;
	int			env_len;
	t_env_list	*target;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (get_quote_type(token, s[i]) != S_QUOTE && s[i] == '$')
		{
			target = get_target(env, &s[i + 1]);
			if (target)
			{
				len += ft_strlen(target->value);
				if (split_data(token, target->value) == -1)
					len -= 1;
			}
			env_len = get_env_len(&s[i + 1]);
			i += env_len + 1;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

int	include_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isquote(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	env_expansion(t_token *token, t_env_list *env, char *s, char *ret)
{
	int			len;
	int			is_split;
	char		**value_set;
	t_env_list	*target;

	len = 0;
	target = get_target(env, s);
	if (target)
	{
		token->quote_in_env = include_quote(target->value);
		is_split = split_data(token, target->value);
		if (is_split)
		{
			value_set = ft_split2(target->value, "\x20\t\v\n\r\f");
			if (is_split == -1)
			{
				*ret = ' ';
				len += join_env_str(token, ret + 1, len, value_set);
			}
			else
				len += join_env_str(token, ret, len, value_set);
		}
		else
		{
			ft_strlcat(ret, target->value, ft_strlen(target->value) + 1);
			len += ft_strlen(target->value);
		}
	}
	else
		token->data = NULL;
	return (len);
}

int	interpreter(t_token *token, char *s, t_env_list *env, int len)
{
	int			i;
	int			j;
	int			type;
	char		*ret;

	i = 0;
	j = 0;
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		perror("malloc error");
	while (s[i])
	{
		type = token->quote_type;
		if (get_quote_type(token, s[i]) != S_QUOTE && s[i] == '$')
		{
			if (j != 0)
				token->space = 1;
			j += env_expansion(token, env, &s[i + 1], &ret[j]);
			i += get_env_len(&s[i + 1]) + 1;
		}
		else
		{
			if (type == token->quote_type)
				ret[j++] = s[i];
			i++;
		}
	}
	free(token->data);
	token->data = ret;
	return (0);
}

int	token_interpreter(t_token **head, t_env_list *env)
{
	int		len;
	t_token	*curr;

	curr = *head;
	while (curr)
	{
		curr->quote_type = DEFAULT;
		if (valid_quote(curr))
			return (1);
		len = interprete_str_len(curr, curr->data, env);
		interpreter(curr, curr->data, env, len);
		//remove_quote(curr, quote_len(curr));s
		curr = curr->next;
	}
	return (0);
}
