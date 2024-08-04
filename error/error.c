/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:08:33 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/04 11:56:48 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	error_msg_with_status(char *cmd, char *path, char *msg, int status)
{
	printf("minishell: %s: %s: %s\n", cmd, path, msg);
	return (status);
}
