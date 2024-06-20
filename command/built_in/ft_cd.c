/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:16:09 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/20 12:53:05 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	ft_cd(t_parser *parser, t_env_list *env)
{
	int		ret;
	char	*path;
	char	*pwd;
	char	*old_pwd;

	old_pwd = ft_pwd(1);
	path = parser->command->target[1];
	if (path == NULL)
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
