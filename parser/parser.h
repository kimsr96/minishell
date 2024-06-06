/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:36:13 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/06 12:43:05 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../tokenizer/tokenizer.h"

typedef struct s_command
{
	char	*cmd;
	char	*flag;
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

/* parse_token.c */
void		parsing_token(t_token *tokens);

/* parser_utils.c */
char		**join_str(char **s1, char *s2);
t_parser	*new_parser(t_tokentype type);
void		add_back_parser(t_parser **head, t_parser *new_parser);

/* parser_free.c */
char		**free_str(char **s);

#endif