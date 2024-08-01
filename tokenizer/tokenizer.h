/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:00:19 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/01 18:24:37 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdio.h>
# include <stdlib.h>
# include "../env/env.h"
# include "../libft/libft.h"

typedef enum e_quotetype
{
	DEFAULT = 0,
	S_QUOTE,
	D_QUOTE
}			t_quotetype;

typedef enum e_tokentype
{
	CMD = 0,
	PIPE,
	REDIRECT
}				t_tokentype;

typedef struct s_token
{
	int					type;
	int					quote_type;
	char				*data;
	struct s_token		*next;
}						t_token;

/* env_parser.c */
void		env_token(t_token **head, t_env_list *env);

/* quote_token_utils.c */
int			quote_len(t_token *token);
int			get_quote_type(t_token *token, char c);
int			double_quote_exception(char a, char b);
char		*realloc_without_quote(char *s, char x, size_t len);

/* quote_token.c */
int			quote_token(t_token **head);

/* tokenizer.c */
int			tokenizer(t_token **head, char *s, t_env_list *env);

/* token_utils.c */
int			get_env_len(char *s);
void		add_back_token(t_token **head, t_token *new);
void		free_token(t_token	*token);
t_token		*new_token(char *s, int len);

#endif