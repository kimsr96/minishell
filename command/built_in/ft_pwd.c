/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:13:51 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/15 16:43:49 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

char	*ft_pwd(int flag)
{
	char	*pwd;

	pwd = (char *)malloc(1024 * sizeof(char));
	if (!pwd)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}
	if (flag)
		return (getcwd(pwd, 1024));
	if (getcwd(pwd, 1024))
	{
		printf("%s\n", pwd);
		return (pwd);
	}
	else
	{
		perror("getcwd failed");
		free(pwd);
		return (NULL);
	}
}
