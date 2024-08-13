/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:09:47 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/13 13:58:28 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	*free_node(t_env_list *argv)
{
	free(argv->key);
	free(argv->value);
	free(argv);
	return (NULL);
}

void	connect_node(t_env_list *curr, t_env_list *argv)
{
	while (curr)
	{
		if (curr->next == argv)
		{
			curr->next = argv->next;
			break ;
		}
		curr = curr->next;
	}
}

int	ft_unset(t_env_list *head, char **str)
{
	int			i;
	t_env_list	*curr;
	t_env_list	*argv;

	i = 0;
	while (str[++i])
	{
		curr = head;
		if (check_key_name(str[i]))
			return (export_unset_error("unset", str[i], NOT_VALID_IDENT));
		argv = find_key_node(head, str[i]);
		if (argv)
		{
			connect_node(curr, argv);
			argv = free_node(argv);
		}
	}
	return (0);
}
