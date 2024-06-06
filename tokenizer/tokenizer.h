/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:00:19 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/06 13:17:00 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../built_in/built_in.h"

typedef enum e_tokentype
{
	WORD = 0,
	QUOTED_WORD,
	PIPE,
	IN_REDIRECT,
	OUT_REDIRECT,
	ENV,
	CMD,
	FLAG
}				t_tokentype;

typedef struct s_token
{
	int					type;
	char				*data;
	struct s_token		*next;
}						t_token;

/* command_token.c */
void		check_cmd(t_token *token);

/* env_parser.c */
void		parse_env(t_token *tokens);

/* quote_parser_utils.c */
int			quote_len(char *s, char x);
int			double_quote_exception(char a, char b);
char		*realloc_without_quote(char *s, char x, size_t len);

/* quote_parser.c */
void		parse_quote(t_token *tokens);

/* tokenizer.c */
t_token		*tokenizer(char *s);

/* token_utils.c */
void		add_back_token(t_token **head, t_token *new);
void		free_token(t_token	*token);
t_token		*new_token(char *s, int len, int quote);

/* tokenizer.c */
void		print_token(t_token	*token);
#endif