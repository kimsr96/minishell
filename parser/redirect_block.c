/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_block.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:45:27 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/03 16:04:10 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir_type	set_redirect_type(char *s)
{
	if (!ft_strncmp(s, "<<", 2))
		return (HEREDOC_REDIRECT);
	else if (!ft_strncmp(s, "<", 1))
		return (IN_REDIRECT);
	else if (!ft_strncmp(s, ">>", 2))
		return (APPEND_REDIRECT);
	else if (!ft_strncmp(s, ">", 1))
		return (OUT_REDIRECT);
	else
		return (-1);
}

int	is_redirect(t_tokentype type)
{
	if (type == REDIRECT)
		return (1);
	else
		return (0);
}

t_redirect	*get_redirect(t_token *token, t_redir_type type)
{
	t_redirect	*redirect;

	redirect = ft_calloc(1, sizeof(t_redirect));
	if (!redirect)
		exit(1);
	redirect->io_type = type;
	if (type == HEREDOC_REDIRECT)
	{
		redirect->delimiter = token->next->data;
		redirect->file_name = NULL;
	}
	else
	{
		redirect->delimiter = NULL;
		redirect->file_name = token->next->data;
	}
	return (redirect);
}

void	add_back_redirect(t_redirect **head, t_redirect *new_redirect)
{
	t_redirect	*curr;

	curr = *head;
	if (!curr)
		*head = new_redirect;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new_redirect;
	}
}
