/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:16:09 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/04 12:30:59 by seungryk         ###   ########.fr       */
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
	path = block->command->target[1];
	if (path == NULL || ft_strncmp(path, "~", 1) == 0)
	{
		env = find_key_node(head, "HOME");
		if (!env)
			return (error_msg_with_status("cd", "HOME", NOT_SET, 1));
		path = env->value;
	}
	ret = chdir(path);
	if (ret == -1)
		return (error_msg_with_status("cd", path, NO_FILE_DIR, 1));
	pwd = getcwd(NULL, 0);
	change_value(head, "PWD", pwd);
	change_value(head, "OLDPWD", old_pwd);
	return (0);
}
