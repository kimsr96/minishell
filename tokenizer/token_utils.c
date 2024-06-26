/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:02:39 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/26 17:33:53 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	get_env_len(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			len++;
		i++;
	}
	return (len);
}

void	add_back_token(t_token **head, t_token *new)
{
	t_token	*curr;

	curr = *head;
	if (!curr)
		*head = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	free_token(t_token	*token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		free(token->data);
		free(token);
		token = next;
	}
}

void	token_type(t_token *token, char *s, int quote)
{
	if (quote)
		token->type = WORD;
	else if (!ft_strncmp(s, "|", 1))
		token->type = PIPE;
	else if (!ft_strncmp(s, "<", 1))
		token->type = IN_REDIRECT;
	else if (!ft_strncmp(s, "<<", 2))
		token->type = HEREDOC_REDIRECT;
	else if (!ft_strncmp(s, ">", 1))
		token->type = OUT_REDIRECT;
	else if (!ft_strncmp(s, ">>", 2))
		token->type = APPEND_REDIRECT;
	else
		token->type = WORD;
}

t_token	*new_token(char *s, int len, int quote)
{
	int			i;
	t_token		*token;

	i = 0;
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		exit(1);
	token->next = NULL;
	token->data = ft_calloc(len + 1, sizeof(char));
	if (!(token->data))
		exit(1);
	token->data[len] = '\0';
	while (i < len)
	{
		token->data[i] = s[i];
		i++;
	}
	token_type(token, token->data, quote);
	return (token);
}
