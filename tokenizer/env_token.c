/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:42:02 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/05 20:25:28 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*get_env_var_name(char *s, int len)
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
	while (s[i] && i < len)
	{
		if (s[i] != '\'' && s[i] != '"')
			env_s[j++] = s[i];
		i++;
	}
	return (env_s);
}

void	join_env_str(t_token *token, int len, char **value_set)
{
	int		i;
	int		j;
	char	*s1;
	t_token	*n_token;

	i = 0;
	j = 0;
	s1 = alloc_ret_str(len);
	while (i < len)
	{
		s1[i] = token->data[i];
		i++;
	}
	free(token->data);
	token->data = ft_strjoin(s1, value_set[j]);
	free(s1);
	while (value_set[++j])
	{
		n_token = new_token(value_set[j], ft_strlen(value_set[j]));
		n_token->next = token->next;
		token->next = n_token;
		token = n_token;
	}
	value_set = free_str(value_set);
}

static int	get_env_string(t_token *token, char *s, t_env_list *env)
{
	size_t		i;
	char		*find_key;
	t_env_list	*target;

	i = 0;
	target = NULL;
	while (s[i] && s[i] != '$')
		i++;
	if (!s[i])
		return (0);
	else if (s[i] == '$')
	{
		find_key = get_env_var_name(&s[i + 1], get_env_len(&s[i + 1]));
		target = find_key_node(env, find_key);
		free(find_key);
		if (!target)
			return (-1);
	}
	if (ft_strncmp(target->key, "?", 1) == 0)
		token->data = ft_strjoin(target->value, &s[i + 2]);
	else
		join_env_str(token, i, ft_split2(target->value, "\x20\t\v\n\r\f"));
	return (0);
}

int	env_token(t_token **head, t_env_list *env)
{
	t_token	*curr;

	curr = *head;
	while (curr)
	{
		if (get_env_string(curr, curr->data, env) == -1)
			curr->data = NULL;
		curr = curr->next;
	}
	if (del_token(head))
		return (1);
	return (0);
}
