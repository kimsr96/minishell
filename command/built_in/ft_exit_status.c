/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:34:09 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/24 16:33:14 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void    ft_exit_status(void)
{
    printf("minishell: %d: command not found\n", status);
    status = 127;
}