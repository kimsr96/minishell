/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_err_exception.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:36:58 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/20 14:58:21 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	env_err(t_block **b_head, t_env_list *env)
{
	int		i;
	t_block	*b_curr;

	b_curr = *b_head;
	while (b_curr)
	{
		if (b_curr->command && b_curr->command->argv)
		{
			i = 0;
			if (!ft_strncmp(b_curr->command->argv[i], "env", 4))
			{
				while (b_curr->command->argv[i])
					i++;
				if (i > 1)
					return (parsing_error(env, ERR_ENV, 1));
			}
		}
		b_curr = b_curr->next;
	}
	return (0);
}

int	redir_err(t_token **t_head, t_env_list *env)
{
	t_token	*t_curr;

	t_curr = *t_head;
	while (t_curr->next)
	{
		if (t_curr->type == REDIRECT && t_curr->next->type == REDIRECT)
			return (parsing_error(env, ERR_SYNTAX, 258));
		t_curr = t_curr->next;
	}
	return (0);
}

int	token_err(t_token **t_head, t_env_list *env)
{
	t_token	*t_curr;

	t_curr = *t_head;
	while (t_curr)
	{
		if (t_curr->err)
			return (parsing_error(env, ERR_SYNTAX, 258));
		t_curr = t_curr->next;
	}
	return (0);
}

int	block_err(t_block **b_head, t_env_list *env)
{
	t_block	*b_curr;

	b_curr = *b_head;
	if (!b_curr)
		return (0);
	if (env_err(b_head, env))
		return (1);
	b_curr = *b_head;
	while (b_curr->next)
	{
		if (b_curr->type == PIPE && b_curr->next->type == PIPE)
			return (parsing_error(env, ERR_SYNTAX, 258));
		b_curr = b_curr->next;
	}
	if (b_curr->type == PIPE)
		return (parsing_error(env, ERR_SYNTAX, 258));
	return (0);
}
