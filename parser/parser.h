/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:36:13 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/30 14:44:48 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../tokenizer/tokenizer.h"
# include "../env/env.h"

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
	char			*cmd_path;
	char			**target;
	t_redirect		*redirect;
}t_command;

typedef struct s_block
{
	int				type;
	t_command		*command;
	struct s_block	*next;
}t_block;


/* parse_token.c */
int				parsing_token(t_block **head, t_token *tokens, t_env_list *env);

/* parser_utils.c */
char			**join_str(char **s1, char *s2);
t_block			*new_block(t_tokentype type);
void			add_back_block(t_block **head, t_block *new_block);

/* parser_free.c */
char			**free_str(char **s);
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
void			remove_block(t_block **head, t_block *cur_block);
t_redirect		*get_redirect(t_token *token, t_redir_type type);
t_redir_type	set_redirect_type(char *s);

/* env_exception.c */
void			env_exception(t_command *cmd);

/* pipe_exception */
int				last_block_pipe_exception(t_block **head);
#endif