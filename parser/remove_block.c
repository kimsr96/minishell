/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:30:53 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/13 15:11:35 by seungryk         ###   ########.fr       */
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
