/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_interpreter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:46:42 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/24 14:51:35 by seungryk         ###   ########.fr       */
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

int	without_quote_len(t_token *token)
{
	int	i;
	int	len;
	int	type;

	i = 0;
	len = 0;
	type = 0;
	while (token->data[i])
	{
		type = token->quote_type;
		get_quote_type(token, token->data[i]);
		if (type == token->quote_type)
			len++;
		i++;
	}
	return (len);
}

char	*remove_quote(t_token *token, int len)
{
	int		i;
	int		idx;
	char	*ret;

	i = 0;
	idx = 0;
	if (token->quote_in_env)
		return (NULL);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		exit(1);
	ret[len] = '\0';
	while (token->data[i])
	{
		if (get_quote_type(token, token->data[i]))
			ret[idx++] = token->data[i];
		i++;
	}
	free(token->data);
	return (ret);
}

int	check_heredoc_expansion(t_token *token)
{
	int	len;

	if (token->type == REDIRECT)
	{
		if (!ft_strncmp(token->data, "<<", 3))
		{
			token->cnt_heredoc++;
			len = without_quote_len(token->next);
			if (token->next->data != NULL && \
					ft_strlen(token->next->data) != (size_t)len)
				token->next->env_heredoc = 1;
			token->next->data = remove_quote(token->next, len);
			return (1);
		}
	}
	return (0);
}
