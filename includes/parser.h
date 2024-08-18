/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:36:13 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/18 17:13:25 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "error.h"
# include "tokenizer.h"
# include "env.h"

typedef enum e_tokentype	t_tokentype;
typedef struct s_token		t_token;

typedef enum e_redir_type
{
	IN_REDIRECT,
	HEREDOC_REDIRECT,
	OUT_REDIRECT,
	APPEND_REDIRECT
}			t_redir_type;

typedef struct s_redirect
{
	int					io_type;
	char				*delimiter;
	char				*file_name;
	struct s_redirect	*next;
}t_redirect;

typedef struct s_command
{
	int				is_empty;
	char			*cmd_path;
	char			**argv;
	t_redirect		*redirect;
}t_command;

typedef struct s_block
{
	int				type;
	t_command		*command;
	struct s_block	*next;
}t_block;

/* parse_token.c */
int				parsing_token(t_block **b_head, t_env_list *env, char *str);

/* parser_utils.c */
void			join_str(t_command *cmd, t_env_list *env, char *data);
t_block			*new_block(t_tokentype type);
void			add_back_block(t_block **head, t_block *new_block);

/* parser_free.c */

void			free_block_all(t_block *block);
void			free_block(t_block	*block);

/* command_path.c */
char			**get_path(t_env_list *env);
char			*get_cmd(t_env_list *env, char *cmd);
char			*case_only_cmd(char **path, char *cmd);
void			free_2darr(char **s);

/* redirect_block.c */
int				is_redirect(t_tokentype type);
void			add_back_redirect(t_redirect **head, t_redirect *new_redirect);
t_redirect		*get_redir(t_token *token, t_redir_type type);
t_redir_type	set_redirect_type(char *s);

/* env_exception.c */
int				env_exception(t_command *cmd);

/* block_exception */
int				block_err(t_block **b_head, t_env_list *env);
int				token_err(t_token **t_head, t_env_list *env);

#endif