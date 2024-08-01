/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:42:02 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/01 18:44:15 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static char	*get_env_var_name(char *s, int len)
{
	int		i;
	int		j;
	char	*env_s;

	i = 0;
	j = 0;
	env_s = malloc(sizeof(char) * (len + 1));
	if (!env_s)
		return (NULL);
	env_s[len] = '\0';
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			env_s[j++] = s[i];
		i++;
	}
	return (env_s);
}

static char	*get_return_string(char *s, char *new_value)
{
	char	*ret;
	size_t	s_len;
	size_t	value_len;

	s_len = 0;
	while (s[s_len] && s[s_len] != '$')
		s_len++;
	value_len = ft_strlen(new_value);
	ret = malloc(sizeof(char) * (s_len + value_len + 1));
	if (!ret)
		exit(1);
	ret[s_len + value_len] = '\0';
	return (ret);
}

static void	join_env_str(t_token *token, char *old_key, char *new_value)
{
	int		i;
	int		j;
	int		idx;
	char	*ret;

	i = 0;
	j = -1;
	idx = 0;
	ret = get_return_string(old_key, new_value);
	while (old_key[i])
	{
		if (old_key[i] == '$')
		{
			while (new_value[++j])
				ret[idx++] = new_value[j];
			i += get_env_len(&old_key[i]);
		}
		else
			ret[idx++] = old_key[i++];
	}
	free(token->data);
	token->data = ret;
}

static void	get_env_string(t_token *token, char *s, t_env_list *env)
{
	size_t		i;
	char		*find_key;
	t_env_list	*target;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			find_key = get_env_var_name(&s[i + 1], get_env_len(&s[i + 1]));
			target = find_key_node(env, find_key);
			if (!target)
			{
				free(token->data);
				token->data = NULL;
				return ;
			}
			break ;
		}
		i++;
	}
	if (i == ft_strlen(s))
		return ;
	join_env_str(token, token->data, target->value);
}

void	env_token(t_token **head, t_env_list *env)
{
	t_token	*curr;

	curr = *head;
	while (curr)
	{
		get_env_string(curr, curr->data, env);
		curr = curr->next;
	}
}
