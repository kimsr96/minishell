/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 09:25:07 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/01 19:00:04 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**get_path(t_env_list *env)
{
	char		**ret;
	t_env_list	*path;

	path = find_key_node(env, "PATH");
	if (!path)
		perror("path");
	if (path)
	{
		ret = ft_split(path->value, ':');
		if (!ret)
			perror("error\n");
		return (ret);
	}
	return (0);
}

char	*get_cmd(t_env_list *env, char *cmd)
{
	char	**path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			perror("command not found\n");
	}
	path = get_path(env->next);
	if (!path)
		return (0);
	return (case_only_cmd(path, cmd));
}

char	*case_only_cmd(char **path, char *cmd)
{
	char	*cmd_path;
	int		i;
	char	*tmp;

	tmp = ft_strjoin("/", cmd);
	if (!tmp)
		perror("malloc error\n");
	i = 0;
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], tmp);
		if (!cmd_path)
			perror("malloc error\n");
		if (access(cmd_path, X_OK) == 0)
		{
			free_2darr(path);
			free(tmp);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_2darr(path);
	free(tmp);
	return (0);
}

void	free_2darr(char **s)
{
	int	idx;

	if (!s)
		return ;
	idx = 0;
	while (s[idx])
	{
		free(s[idx]);
		idx++;
	}
	free(s);
	s = 0;
}
