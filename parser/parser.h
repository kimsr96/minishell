/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 08:36:13 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/06 15:52:23 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../tokenizer/tokenizer.h"
# include "../env/env.h"

typedef struct s_command
{
	char	*cmd_path;
	char	**target;
}t_command;

typedef struct s_redirect
{
	int		io_type;
	char	*delimiter;
	char	*file_name;	
}t_redirect;

typedef struct s_block
{
	int				type;
	t_command		*command;
	t_redirect		*redirection;
	struct s_block	*next;
}t_block;

/* parse_token.c */
void		parsing_token(t_block **head, t_token *tokens, t_env_list *env);

/* parser_utils.c */
char		**join_str(char **s1, char *s2);
t_block		*new_block(t_tokentype type);
void		add_back_block(t_block **head, t_block *new_block);

/* parser_free.c */
t_block		*init_block(void);
char		**free_str(char **s);
void		free_block_all(t_block *block);
void		free_block(t_block	*block);

/* command_path.c */
char		**get_path(t_env_list *env);
char		*get_cmd(t_env_list *env, char *cmd);
char		*case_only_cmd(char **path, char *cmd);
void		free_2darr(char **s);

void		remove_block(t_block **head, t_block *cur_block);

#endif