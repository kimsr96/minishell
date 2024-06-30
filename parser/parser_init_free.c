/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_init_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:08:30 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/26 22:20:35 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_block	*init_block(void)
{
	int			len;
	t_block		*block;

	len = 0;
	block = (t_block *)ft_calloc(1, sizeof(t_block));
	if (!block)
		exit(1);
	return (block);
}

char	**free_str(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	s = NULL;
	return (s);
}

void	free_block(t_block	*block)
{
	t_block	*next;

	while (block)
	{
		next = block->next;
		if (block->command)
			free_str(block->command->target);
		block = next;
	}
}
