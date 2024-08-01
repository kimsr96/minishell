/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:16:09 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/01 15:20:24 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_cd(t_block *parser, t_env_list *env)
{
	int		ret;
	char	*path;
	char	pwd[1024];
	char	old_pwd[1024];

	getcwd(old_pwd, 1024);
	path = parser->command->target[1];
	if (path == NULL || ft_strncmp(path, "~", 1) == 0)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	else
	{
		ret = chdir(path);
		if (ret == -1)
		{
			printf("bash: cd: %s: No such file or dircetory\n", path);
			return (1);
		}
	}
	getcwd(pwd, 1024);
	change_env_value(env, "PWD", pwd);
	change_env_value(env, "OLDPWD", old_pwd);
	return (0);
}
