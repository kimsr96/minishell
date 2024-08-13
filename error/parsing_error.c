/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:04:45 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/13 15:10:56 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	parsing_error(t_env_list *env, char *msg, int status)
{
	printf("minishell: %s\n", msg);
	free(env->value);
	env->value = ft_itoa(status);
	return (status);
}
