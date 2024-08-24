/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:46:30 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/24 14:50:38 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	line_to_env(t_env_list *env, char *s, char *ret)
{
	int			len;
	t_env_list	*target;

	len = 0;
	target = get_target(env, s);
	if (target)
	{
		ft_strlcat(ret, target->value, ft_strlen(target->value) + 1);
		len += ft_strlen(target->value);
	}
	return (len);
}

static int	heredoc_is_expansion(t_env_list *env, char *s)
{
	if (*s == '$' && *(s + 1) != '=' && *(s + 1))
	{
		if (get_target(env, s + 1))
			return (1);
		else
			return (-1);
	}
	else
		return (0);
}

static int	heredoc_env_len( t_env_list *env, char *s)
{
	int			i;
	int			len;
	int			expansion;
	t_env_list	*target;

	i = 0;
	len = 0;
	while (s[i])
	{
		expansion = heredoc_is_expansion(env, &s[i]);
		if (expansion == 1)
		{
			target = get_target(env, &s[i + 1]);
			len += ft_strlen(target->value);
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

char	*heredoc_env_expansion(t_env_list *env, char *line, int expansion)
{
	int		i;
	int		j;
	int		len;
	char	*ret;

	i = -1;
	j = 0;
	if (expansion)
		return (ft_strdup(line));
	len = heredoc_env_len(env, line);
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		exit(1);
	ret[len] = '\0';
	while (line[++i])
	{
		if (heredoc_is_expansion(env, &line[i]) && !expansion)
		{			
			j += line_to_env(env, &line[i + 1], &ret[j]);
			i += get_env_len(&line[i + 1]);
		}
		else
			ret[j++] = line[i];
	}
	return (ret);
}
