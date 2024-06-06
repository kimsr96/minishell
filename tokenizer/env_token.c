/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:42:02 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/06 12:41:06 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static char	*get_env_var_name(char *s, int len)
{
	int		i;
	char	*env_s;

	i = 0;
	env_s = malloc(sizeof(char) * (len + 1));
	if (!env_s)
		return (NULL);
	env_s[len] = '\0';
	len = 0;
	while (s[i])
	{
		if (s[i] == '$')
			i++;
		else
		{
			env_s[len] = s[i];
			i++;
			len++;
		}
	}
	return (env_s);
}

static char	*join_env_str(char *s, size_t s_len, char *env)
{
	int		e_idx;
	char	*r;
	size_t	len;
	size_t	idx;

	idx = -1;
	e_idx = 0;
	if (!env)
		len = s_len;
	else
		len = s_len + ft_strlen(env);
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		exit(1);
	r[len] = '\0';
	while (++idx < s_len)
		r[idx] = s[idx];
	while (idx < len)
	{
		r[idx] = env[e_idx];
		idx++;
		e_idx++;
	}
	free(s);
	return (r);
}

static void	get_env_string(t_token *token, char *s)
{
	size_t	i;
	size_t	j;
	char	*var_name;
	char	*env;

	i = 0;
	j = 0;
	env = NULL;
	while (s[i])
	{
		if (s[i] == '$')
		{
			j = i + 1;
			var_name = get_env_var_name(&s[j], ft_strlen(&s[j]));
			env = getenv(var_name);
			break ;
		}
		i++;
	}
	if (i == ft_strlen(s))
		return ;
	token->data = join_env_str(s, i, env);
}

void	parse_env(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type != QUOTED_WORD)
			get_env_string(curr, curr->data);
		curr = curr->next;
	}
}
