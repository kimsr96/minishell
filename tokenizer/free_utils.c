/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:03:45 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/13 15:09:17 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

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

void	delete_token(t_token **head)
{
	t_token	*curr;
	t_token	*temp;

	curr = *head;
	while (curr)
	{
		if (curr->next)
		{
			if (curr->next->data == NULL)
			{
				temp = curr->next->next;
				free(curr->next->data);
				free(curr->next);
				curr->next = temp;
			}
		}
		curr = curr->next;
	}
}

void	free_all_token(t_token	*token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		if (token->data)
			free(token->data);
		free(token);
		token = next;
	}
}
