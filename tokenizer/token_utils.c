/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:02:39 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/07 12:28:39 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	token_type(t_token *token, char *s, int quote)
{
	if (quote)
		token->type = WORD;
	else if (!ft_strncmp(s, "|", 1))
		token->type = PIPE;
	else if (!ft_strncmp(s, "<", 1) || !ft_strncmp(s, "<<", 2))
		token->type = IN_REDIRECT;
	else if (!ft_strncmp(s, ">", 1) || !ft_strncmp(s, ">>", 2))
		token->type = OUT_REDIRECT;
	else
		token->type = WORD;
}

t_token	*new_token(char *s, int len, int quote)
{
	int			i;
	t_token		*token;

	i = 0;
	token = malloc(sizeof(t_token));
	if (!token)
		exit(1);
	token->next = NULL;
	token->data = malloc(sizeof(char) * (len + 1));
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
