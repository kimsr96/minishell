/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_err_exception.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:36:58 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/11 17:18:29 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	block_err_exception(t_block **b_head, t_token **t_head, t_env_list *env)
{
	t_block	*b_curr;
	t_token	*t_curr;

	b_curr = *b_head;
	t_curr = *t_head;
	if (!b_curr)
		return (0);
	while (b_curr->next)
		b_curr = b_curr->next;
	if (b_curr->type == PIPE)
		return (parsing_error(env, ERR_PIPE, 127));
	else
		return (0);
	while (t_curr)
	{
		if (t_curr->err)
			return (1);
		t_curr = t_curr->next;
	}
	return (0);
}
