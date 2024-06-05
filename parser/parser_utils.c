/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:24:40 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/05 15:14:18 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**join_str_first(char **s1, char *s2)
{
	char	**ret;

	ret = ft_calloc(2, sizeof(char *));
	if (!ret)
		exit(1);
	ret[0] = s2;
	ret[1] = NULL;
	return (ret);
}

char	**attach_data(char **s1, char *s2, int len)
{
	int		i;
	char	**ret;

	i = 0;
	ret = ft_calloc(len + 1, sizeof(char *));
	if (!ret)
		exit(1);
	ret[len] = NULL;
	ret[len - 1] = s2;
	while (i < len)
	{
		ret[i] = ft_strdup(s1[len]);
		if (!ret[i])
			exit(1);
		i++;
	}
	return (ret);
}

char	**join_str(char **s1, char *s2)
{
	int		len;
	char	**ret;

	len = 0;
	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (join_str_first(s1, s2));
	while (s1[len])
		len++;
	ret = attach_data(s1, s2, len);
	free(s2);
	s2 = NULL;
	s1 = free_str(s1);
	return (ret);
}

t_parser	*new_parser(t_tokentype type)
{
	int			i;
	t_parser	*parser;

	i = 0;
	parser = malloc(sizeof(t_parser));
	if (!parser)
		exit(1);
	parser->next = NULL;
	parser->type = type;
	return (parser);
}

void	add_back_parser(t_parser **head, t_parser *new_parser)
{
	t_parser	*curr;

	curr = *head;
	if (!curr)
		*head = new_parser;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new_parser;
	}
}