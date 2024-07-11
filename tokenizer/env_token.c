/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:42:02 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/11 14:56:10 by hyeonble         ###   ########.fr       */
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

static char	*get_return_string(char *s, char *env)
{
	char	*ret;
	size_t	s_len;
	size_t	e_len;

	s_len = 0;
	while (s[s_len] && s[s_len] != '$')
		s_len++;
	e_len = ft_strlen(env);
	ret = malloc(sizeof(char) * (s_len + e_len + 1));
	if (!ret)
		exit(1);
	ret[s_len + e_len] = '\0';
	return (ret);
}

static char	*join_env_str(char *s, char *env)
{
	int		i;
	int		j;
	int		idx;
	char	*ret;

	i = 0;
	j = -1;
	idx = 0;
	ret = get_return_string(s, env);
	while (s[i])
	{
		if (s[i] == '$')
		{
			while (env[++j])
				ret[idx++] = env[j];
			i += get_env_len(&s[i]);
		}
		else
		{
			ret[idx++] = s[i];
			i++;
		}
	}
	return (ret);
}

static void	get_env_string(t_token *token, char *s)
{
	size_t	i;
	char	*ret;
	char	*env;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			env = getenv(get_env_var_name(&s[i + 1], get_env_len(&s[i + 1])));
			if (!env)
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
	ret = join_env_str(token->data, env);
	free(token->data);
	token->data = ret;
}

void	env_token(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (ft_strncmp(curr->data, "$?", 2) == 0)
			curr = curr->next;
		else
		{
			get_env_string(curr, curr->data);
			curr = curr->next;
		}
	}
}
