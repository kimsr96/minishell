/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:09:44 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/18 19:35:23 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	check_key_name(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (i == 0 && !ft_isalpha(s[i]))
			return (1);
		if (!ft_isalnum(s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	put_env(t_env_list *head, char *s)
{
	int			key_len;
	int			value_len;
	char		*key;
	char		*value;

	key_len = get_key_len(s);
	value_len = ft_strlen(s) - (key_len + 1);
	key = get_key(s, key_len);
	value = get_value(s, value_len);
	if (check_key_name(key) || key_len == -1 || key_len == 0)
	{
		free(key);
		free(value);
		return (export_unset_error("export", s, NOT_VALID_IDENT));
	}
	if (ft_strnstr(s, "+=", ft_strlen(s)))
		add_env_value(head, key, value);
	else if (ft_strnstr(s, "=", ft_strlen(s)) || (key && value == NULL))
		change_add_value(head, key, value);
	return (0);
}

int	ft_export(t_env_list *head, char **str)
{
	int	i;

	i = 1;
	head = head->next;
	if (str[i] == NULL)
		sort_print_env(head);
	else
	{
		while (str[i])
		{
			if (put_env(head, str[i]))
				return (1);
			i++;
		}
	}
	return (0);
}
