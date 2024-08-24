/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:12:22 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/22 18:46:07 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	interprete_str_len(t_token *token, char *s, t_env_list *env)
{
	int			i;
	int			len;
	int			expansion;
	t_env_list	*target;

	i = 0;
	len = 0;
	while (s[i])
	{
		expansion = is_expansion(token, env, &(token->data[i]));
		if (expansion == 1)
		{
			target = get_target(env, &s[i + 1]);
			len += ft_strlen(target->value);
			if (token->is_split == -1)
				len -= 1;
			i += get_env_len(&s[i + 1]);
		}
		else if (expansion == -1)
			i += get_env_len(&s[i + 1]);
		else
			len++;
		i++;
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
	return (len);
}

char	*interpreter(t_token *token, t_env_list *env, char *ret, int len)
{
	int			i;
	int			j;
	int			type;

	i = -1;
	j = 0;
	if (len == 0)
		return (NULL);
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		exit(1);
	while (token->data[++i])
	{
		type = token->quote_type;
		if (is_expansion(token, env, &(token->data[i])))
		{			
			if (j != 0)
				token->space = 1;
			j += env_expansion(token, env, &token->data[i + 1], &ret[j]);
			i += get_env_len(&token->data[i + 1]);
		}
		else if (type == token->quote_type)
			ret[j++] = token->data[i];
	}
	return (ret);
}

int	token_interpreter(t_token **head, t_env_list *env)
{
	char	*ret;
	t_token	*curr;

	curr = *head;
	if (valid_quote(head, env))
		return (1);
	while (curr)
	{
		curr->quote_type = DEFAULT;
		if (check_heredoc_expansion(curr) && curr->next)
			curr = curr->next;
		else
		{
			ret = interpreter(curr, env, ret, \
						interprete_str_len(curr, curr->data, env));
			free(curr->data);
			curr->data = ret;
		}
		curr = curr->next;
	}
	if (!(*head) || del_token(head, env))
		return (1);
	return (0);
}
