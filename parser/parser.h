/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:36:13 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/05 15:09:09 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../tokenizer/tokenizer.h"

typedef struct s_command
{
	int		cmd;
	int		flag;
	char	**target;
}t_command;

typedef struct s_redirect
{
	int		io_type;
	char	*file_name;	
}t_redirect;

typedef struct s_parser
{
	int				type;
	t_command		*command;
	t_redirect		*redirection;
	struct s_parser	*next;
}t_parser;

/* parser_utils.c */
t_parser	*new_parser(t_tokentype type);
void		add_back_parser(t_parser **head, t_parser *new_parser);

/* parser_free.c */
char		**free_str(char **s);
#endif