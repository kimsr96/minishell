/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:24:40 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/17 21:36:08 by hyeonble         ###   ########.fr       */
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

void	join_str(t_command *cmd, t_env_list *env, char *data)
{
	int		len;

	len = 0;
	if (data == NULL)
		return ;
	if (cmd->argv == NULL)
	{
		cmd->cmd_path = get_cmd(env, data);
		cmd->argv = attach_data(cmd->argv, data, len);
	}
	else
	{
		while (cmd->argv[len])
			len++;
		cmd->argv = attach_data(cmd->argv, data, len);
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
