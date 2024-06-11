/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:16:09 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/11 15:11:30 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../command.h"

void	ft_cd(char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret == -1)
	{
		printf("bash: cd: %s: No such file or dircetory\n", path);
		return ;
	}
}
