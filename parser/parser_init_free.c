/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:08:30 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/26 16:54:14 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser	*init_parser(void)
{
	int			len;
	t_parser	*parser;

	len = 0;
	parser = (t_parser *)malloc(sizeof(parser));
	if (!parser)
		exit(1);
	ft_memset(parser, 0, sizeof(parser));
	return (parser);
}

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

void	free_parser(t_parser	*parser)
{
	t_parser	*next;

	while (parser)
	{
		next = parser->next;
		if (parser->command)
			free_str(parser->command->target);
		parser = next;
	}
}
