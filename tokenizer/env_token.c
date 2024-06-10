/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:42:02 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/10 15:37:20 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	env_len(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			len++;
		i++;
	}
	return (len);
}

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

static char	*join_env_str(char *s, char *env)
{
	int		i;
	int		j;
	int		idx;
	size_t	s_len;
	size_t	e_len;
	char	*ret;

	i = 0;
	j = 0;
	idx = 0;
	s_len = ft_strlen(s) - env_len(s);
	e_len = ft_strlen(env);
	ret = malloc(sizeof(char) * (s_len + e_len + 1));
	if (!ret)
		exit(1);
	while (s[i])
	{
		if (s[i] == '$')
		{
			while (env[j])
			{
				ret[idx++] = env[j];
				j++;
			}
			i += env_len(s);
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
	env = NULL;
	while (s[i])
	{
		if (s[i] == '$')
		{
			env = getenv(get_env_var_name(&s[i + 1], env_len(&s[i + 1])));
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

void	parse_env(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		get_env_string(curr, curr->data);
		curr = curr->next;
	}
}
