/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:09:44 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/04 12:29:12 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	check_key_name(char *s)
{
	if ((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))
		return (0);
	else
		return (1);
}

int	ft_export(t_env_list *head, char **str)
{
	int			key_len;
	int			value_len;
	char		*key;
	char		*value;

	head = head->next;
	if (str[1] == NULL)
		sort_print_env(head);
	else
	{
		key_len = get_key_len(str[1]);
		value_len = ft_strlen(str[1]) - (key_len + 1);
		key = get_key(str[1], key_len);
		value = get_value(str[1], value_len);
		if (check_key_name(str[1]))
		{
			perror("not a valid identifier");
			return (1);
		}
		if (ft_strnstr(str[1], "+=", ft_strlen(str[1])))
			add_env_value(head, key, value);
		else
			change_add_value(head, key, value);
	}
	return (0);
}
