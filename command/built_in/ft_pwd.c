/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:13:51 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/01 15:25:52 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, 1024))
	{
		printf("%s\n", pwd);
		return (0);
	}
	else
	{
		perror("getcwd failed");
		return (1);
	}
}
