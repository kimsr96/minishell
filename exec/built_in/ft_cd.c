/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:16:09 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/17 19:21:53 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static char	*cd_to_path(t_env_list *head,char *path)
{
	char		*ret;
	t_env_list	*env;

	if (path == NULL || !ft_strncmp(path, "~", 2))
		env = find_key_node(head, "HOME");
	else if (!ft_strncmp(path, "-", 2))
		env = find_key_node(head, "OLDPWD");
	else
		env = NULL;
	if (!env)
	{
		cd_error("cd", path, NOT_SET);
		return (NULL);
	}
	ret = env->value;
	if (path != NULL && ft_strncmp(path, "-", 2) == 0)
		ft_putendl_fd(ret, STDOUT_FILENO);
	return (ret);
}

int	ft_cd(t_block *block, t_env_list *head)
{
	int			ret;
	char		*path;
	char		*old_pwd;

	ret = 0;
	path = block->command->argv[1];
	if (path == NULL || !ft_strncmp(path, "~", 2) || !ft_strncmp(path, "-", 2))
		path = cd_to_path(head, path);
	if (!path)
		return (1);
	old_pwd = getcwd(NULL, 0);
	ret = chdir(path);
	if (ret == -1)
	{
		free(old_pwd);
		cd_error("cd", path, NO_FILE_DIR);
		return (1);
	}
	change_value(head, "PWD", getcwd(NULL, 0));
	change_value(head, "OLDPWD", old_pwd);
	return (0);
}
