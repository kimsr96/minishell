/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:00:19 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/21 14:06:28 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef enum e_quotetype
{
	DEFAULT = 0,
	S_QUOTE,
	D_QUOTE
}			t_quotetype;

typedef enum e_tokentype
{
	WORD = 0,
	PIPE,
	IN_REDIRECT,
	OUT_REDIRECT,
	CMD
}				t_tokentype;

typedef struct s_token
{
	int					type;
	int					quote_type;
	char				*data;
	struct s_token		*next;
}						t_token;

/* env_parser.c */
void		env_token(t_token *tokens);

/* quote_token_utils.c */
int			quote_len(t_token *token);
int			get_quote_type(t_token *token, char c);
int			double_quote_exception(char a, char b);
char		*realloc_without_quote(char *s, char x, size_t len);

/* quote_token.c */
void		quote_token(t_token *tokens);

/* tokenizer.c */
t_token		*tokenizer(char *s);

/* token_utils.c */
int			get_env_len(char *s);
void		add_back_token(t_token **head, t_token *new);
void		free_token(t_token	*token);
t_token		*new_token(char *s, int len, int quote);

#endif