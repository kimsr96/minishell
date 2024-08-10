/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exception.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:36:58 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/10 16:24:06 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	last_block_pipe_exception(t_block **head, t_env_list *env)
{
	t_block	*curr;

	curr = *head;
	if (!curr)
		return (0);
	while (curr->next)
		curr = curr->next;
	if (curr->type == PIPE)
		return (parsing_error(env, ERR_PIPE, 127));
	else
		return (0);
}
