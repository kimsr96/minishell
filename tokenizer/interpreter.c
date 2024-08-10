/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:12:22 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/10 14:34:10 by seungryk         ###   ########.fr       */
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
	t_env_list	*target;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (get_quote_type(token, s[i]) != S_QUOTE &&\
				s[i] == '$' && s[i + 1] != '=' && s[i + 1])
		{
			target = get_target(env, &s[i + 1]);
			if (target)
			{
				len += ft_strlen(target->value);
				if (token->is_split == -1)
					len -= 1;
			}
			i += get_env_len(&s[i + 1]) + 1;
			continue ;
		}
		i++;
		len++;
	}
	return (len);
}

int	get_value_set(t_token *token, char *ret, int len, t_env_list *target)
{
	char		**value_set;

	value_set = ft_split2(target->value, "\x20\t\v\n\r\f");
	if (token->is_split == -1)
	{
		*ret = ' ';
		len += join_env_str(token, ret + 1, len, value_set);
	}
	else
		len += join_env_str(token, ret, len, value_set);
	return (len);
}

int	env_expansion(t_token *token, t_env_list *env, char *s, char *ret)
{
	int			len;
	t_env_list	*target;

	len = 0;
	target = get_target(env, s);
	if (target)
	{
		token->quote_in_env = include_quote(target->value);
		split_data(token, target->value);
		if (token->is_split)
			len += get_value_set(token, ret, len, target);
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

void	interpreter(t_token *token, t_env_list *env, char *ret)
{
	int			i;
	int			j;
	int			type;

	i = 0;
	j = 0;
	while (token->data[i])
	{
		type = token->quote_type;
		if (get_quote_type(token, token->data[i]) != S_QUOTE && \
			token->data[i] == '$' && token->data[i + 1] != '=' && \
			token->data[i + 1])
		{
			if (j != 0)
				token->space = 1;
			j += env_expansion(token, env, &token->data[i + 1], &ret[j]);
			i += get_env_len(&token->data[i + 1]) + 1;
			continue ;
		}
		if (type == token->quote_type)
			ret[j++] = token->data[i];
		i++;
	}
	free(token->data);
	token->data = ret;
}

int	token_interpreter(t_token **head, t_env_list *env)
{
	int		len;
	char	*ret;
	t_token	*curr;

	curr = *head;
	while (curr)
	{
		curr->quote_type = DEFAULT;
		if (valid_quote(curr))
			return (1);
		len = interprete_str_len(curr, curr->data, env);
		ret = ft_calloc(len + 1, sizeof(char));
		if (!ret)
			perror("malloc error");
		interpreter(curr, env, ret);
		curr = curr->next;
	}
	return (0);
}
