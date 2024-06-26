/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:16:09 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/26 22:19:22 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	ft_cd(t_block *parser, t_env_list *env)
{
	int		ret;
	char	*path;
	char	*pwd;
	char	*old_pwd;

	old_pwd = ft_pwd(1);
	path = parser->command->target[1];
	if (path == NULL || ft_strncmp(path, "~", 1) == 0)
		chdir(getenv("HOME"));
	else
	{
		ret = chdir(path);
		if (ret == -1)
		{
			printf("bash: cd: %s: No such file or dircetory\n", path);
			return ;
		}
	}
	pwd = ft_pwd(1);
	change_env_value(env, "PWD", pwd);
	change_env_value(env, "OLDPWD", old_pwd);
}
