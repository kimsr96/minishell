/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:09:44 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/19 14:17:15 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	check_key(char *s)
{
	if ((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))
		return (0);
	else
		return (1);
}

void	ft_export(t_env_list *head, char **str)
{
	int			key_len;
	int			value_len;
	char		*key;
	t_env_list	*new_env;

	key_len = get_key_len(str[1]);
	value_len = ft_strlen(str[1]) - (key_len + 1);
	key = get_key(str[1], key_len);
	if (check_key(str[1]))
		perror("not a valid identifier");
	new_env = new_env_list(key, get_value(str[1], value_len));
	add_back_env(&head, new_env);
}
