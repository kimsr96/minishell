/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:16:09 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/13 15:09:54 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_cd(t_block *block, t_env_list *head)
{
	int			ret;
	char		*path;
	char		*pwd;
	char		*old_pwd;
	t_env_list	*env;

	old_pwd = getcwd(NULL, 0);
	path = block->command->argv[1];
	if (path == NULL || ft_strncmp(path, "~", 1) == 0)
	{
		env = find_key_node(head, "HOME");
		if (!env)
			return (cd_error("cd", "HOME", NOT_SET));
		path = env->value;
	}
	ret = chdir(path);
	if (ret == -1)
		return (cd_error("cd", path, NO_FILE_DIR));
	pwd = getcwd(NULL, 0);
	change_value(head, "PWD", pwd);
	change_value(head, "OLDPWD", old_pwd);
	return (0);
}
