/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:24:40 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/23 16:36:10 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**join_str_first(char *s2)
{
	char	**ret;

	ret = ft_calloc(2, sizeof(char *));
	if (!ret)
		exit(1);
	ret[0] = ft_strdup(s2);
	ret[1] = NULL;
	return (ret);
}

static char	**attach_data(char **s1, char *s2, int len)
{
	int		i;
	char	**ret;

	i = 0;
	ret = ft_calloc(len + 2, sizeof(char *));
	if (!ret)
		exit(1);
	ret[len + 1] = NULL;
	ret[len] = ft_strdup(s2);
	while (i < len)
	{
		ret[i] = ft_strdup(s1[i]);
		if (!ret[i])
			exit(1);
		i++;
	}
	return (ret);
}

char	**join_str(char **s1, char *s2)
{
	int		len;
	char	**ret;

	len = 0;
	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (join_str_first(s2));
	while (s1[len])
		len++;
	ret = attach_data(s1, s2, len);
	s2 = NULL;
	s1 = free_str(s1);
	return (ret);
}

t_block	*new_block(t_tokentype type)
{
	t_block	*block;

	block = ft_calloc(1, sizeof(t_block));
	if (!block)
		exit(1);
	block->command = NULL;
	block->next = NULL;
	block->type = type;
	return (block);
}

void	add_back_block(t_block **head, t_block *new_block)
{
	t_block	*curr;

	curr = *head;
	if (!curr)
		*head = new_block;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new_block;
	}
}
