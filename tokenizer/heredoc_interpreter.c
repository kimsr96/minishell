/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_interpreter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:46:42 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/15 17:09:33 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	update_exit_code(int exit_code, t_env_list *env)
{
	if (env->value != NULL)
	{
		free(env->value);
		env->value = NULL;
	}
	env->value = ft_itoa(exit_code);
}

int	check_max_heredoc(t_token *curr, t_env_list *env)
{
	int	num;

	num = 0;
	while (curr)
	{
		if (curr->cnt_heredoc)
			num++;
		curr = curr->next;
	}
	if (num >= 17)
	{
		max_heredoc_error();
		update_exit_code(2, env);
		return (1);
	}
	return (0);
}

int	check_heredoc_expansion(t_token *token)
{
	if (token->type == REDIRECT)
	{
		if (!ft_strncmp(token->data, "<<", 3))
		{
			token->cnt_heredoc++;
			return (1);
		}
	}
	return (0);
}