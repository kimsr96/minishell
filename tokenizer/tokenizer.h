/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:00:19 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/06 15:14:03 by seungryk         ###   ########.fr       */
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
	REDIRECT,
}				t_tokentype;

typedef struct s_token
{
	int					type;
	int					quote_type;
	char				*data;
	struct s_token		*next;
}						t_token;

/* tokenizer.c */
int			tokenizer(t_token **head, char *s, t_env_list *env);

/* token_utils.c */
void		free_all_token(t_token	*token);
char		**free_str(char **s);
int			get_env_len(char *s);
int			del_token(t_token **head);
void		add_back_token(t_token **head, t_token *new);
t_token		*new_token(char *s, int len);

/* interpreter.c */
int			token_interpreter(t_token **head, t_env_list *env);

/* interpreter_utils.c */
int			split_data(char *s);
int			join_env_str(t_token *token, char *ret, int j, char **value_set);

/* quote_token.c */
int			ft_isquote(char c);
int			get_quote_type(t_token *token, char c);
int			valid_quote(t_token *token);
int			quote_len(t_token *token);
void		remove_quote(t_token *token, int len);
#endif