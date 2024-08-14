/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:24:40 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/14 14:35:05 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	free_2darr(s1);
	return (ret);
}

void	join_str(t_command *cmd, char *s2)
{
	int		len;

	len = 0;
	if (s2 == NULL)
		return ;
	if (cmd->argv == NULL)
		cmd->argv = attach_data(cmd->argv, s2, len);
	else
	{
		while (cmd->argv[len])
			len++;
		cmd->argv = attach_data(cmd->argv, s2, len);
	}
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
