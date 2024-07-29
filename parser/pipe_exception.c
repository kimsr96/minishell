/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exception.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:36:58 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/29 17:46:46 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    last_block_pipe_exception(t_block **head)
{
	t_block	*curr;

	curr = *head;
	if (!curr)
		return ;
	while (curr->next)
		curr = curr->next;
	if (curr->type == PIPE)
	{
		perror("pipe error");
		exit(1);	
	}
	else
		return ;
}		
	