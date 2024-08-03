/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:02:39 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/03 13:11:01 by seungryk         ###   ########.fr       */
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
	if (!(token->data))
		exit(1);
	token->data[len] = '\0';
	while (i < len)
	{
		token->data[i] = s[i];
		i++;
	}
	token_type(token, token->data);
	return (token);
}
