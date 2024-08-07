/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:02:39 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/07 11:04:35 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

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

int	del_token(t_token **head)
{
	t_token	*curr;
	t_token	*next;
	t_token	*target;

	curr = *head;
	if (curr->data == NULL)
		return (1);
	while (curr->next)
	{
		if (curr->next->data == NULL)
		{
			target = curr->next;
			next = curr->next->next;
			curr->next = next;
			free(target->data);
			free(target);
			curr = next;
			if (!curr)
				break ;
		}
		else
			curr = curr->next;
	}
	return (0);
}

void	token_type(t_token *token, char *s)
{
	if (!ft_strncmp(s, "|", 1))
		token->type = PIPE;
	else if (!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, "<", 1))
		token->type = REDIRECT;
	else if (!ft_strncmp(s, ">>", 2) || !ft_strncmp(s, ">", 1))
		token->type = REDIRECT;
	else
		token->type = CMD;
}

t_token	*new_token(char *s, int len)
{
	int			i;
	t_token		*token;

	i = 0;
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		exit(1);
	token->next = NULL;
	token->data = ft_calloc(len + 1, sizeof(char));
	if (!token->data)
		exit(1);
	token->data[len] = '\0';
	while (i < len)
	{
		token->data[i] = s[i];
		i++;
	}
	token->space = 0;
	token_type(token, token->data);
	return (token);
}
