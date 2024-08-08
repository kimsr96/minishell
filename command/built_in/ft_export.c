/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:09:44 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/07 17:01:02 by seungryk         ###   ########.fr       */
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

void	put_env(t_env_list *head, char *s)
{
	int			key_len;
	int			value_len;
	char		*key;
	char		*value;

	key_len = get_key_len(s);
	value_len = ft_strlen(s) - (key_len + 1);
	key = get_key(s, key_len);
	value = get_value(s, value_len);
	if (check_key_name(s) || key_len == -1)
	{
		perror("not a valid identifier");
		return ;
	}
	if (ft_strnstr(s, "+=", ft_strlen(s)))
		add_env_value(head, key, value);
	else
		change_add_value(head, key, value);
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
			put_env(head, str[i]);
			i++;
		}
	}
	return (0);
}
