/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raise_parsing_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:04:45 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/17 17:04:20 by hyeonble         ###   ########.fr       */
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
