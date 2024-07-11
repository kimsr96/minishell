/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:30:53 by hyeonble          #+#    #+#             */
/*   Updated: 2024/07/06 15:52:18 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	remove_block(t_block **head, t_block *cur_block)
{
	t_block	*temp;
	t_block	*prev;

	if (!head || !(*head) || !cur_block)
		return ;
	if (*head == cur_block)
	{
		temp = *head;
		*head = (*head)->next;
		free_block(temp);
		return ;
	}
	prev = *head;
	while (prev->next && prev->next != cur_block)
		prev = prev->next;
	if (prev->next == cur_block)
	{
		temp = cur_block;
		prev->next = cur_block->next;
		free_block(temp);
	}
}
