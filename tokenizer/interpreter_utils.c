/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:00:37 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/13 14:01:42 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_env_list	*get_argv(t_env_list *env, char *s)
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

int	is_expansion(t_token *token, t_env_list *env, char *s, int j)
{
	j = 0;
	if (get_quote_type(token, *s) != S_QUOTE && \
			*s == '$' && *(s + 1) != '=' && *(s + 1))
	{
		if (get_argv(env, s + 1))
			return (1);
		else
			return (-1);
	}
	else
		return (0);
}

void	split_data(t_token *token, char *s)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	while (s[space] && ft_isspace(s[space]))
		space++;
	while (s[i])
	{
		if (ft_isspace(s[i]))
			break ;
		i++;
	}
	if ((s[i] == '\0' && !space) || token->quote_type != DEFAULT)
		token->is_split = 0;
	else if (space && token->space)
		token->is_split = -1;
	else
		token->is_split = 1;
}

int	join_env_str(t_token *token, char *ret, int j, char **value_set)
{
	int		i;
	int		len;
	t_token	*n_token;

	i = 0;
	len = 0;
	while (value_set[i][len])
	{
		ret[j++] = value_set[i][len];
		len++;
	}
	while (value_set[++i])
	{
		n_token = new_token(value_set[i], ft_strlen(value_set[i]));
		n_token->next = token->next;
		token->next = n_token;
		token = n_token;
	}
	value_set = free_str(value_set);
	return (len);
}
