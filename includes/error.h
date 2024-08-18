/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:08:35 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/18 17:13:48 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include "parser.h"
# include "env.h"

typedef struct s_block	t_block;

# define COMMAND_NOT_FOUND 1
# define NO_SUCH_FILE_OR_DIR 2
# define IS_A_DIRECTORY 3
# define PERMISSION_DENIED 4
# define NO_FILE_DIR 11
# define NOT_SET 12
# define TOO_MANY_ARG 13
# define NUMERIC_ARG_REQUIRED 14
# define NOT_VALID_IDENT 15
# define ERR_SYNTAX "SyntaxError : invalid syntax"
# define ERR_ENV "env : with no options or arguments"

/* built_in_error.c */
void	cd_error(char *cmd, char *path, int errno);
int		pwd_error(char *cmd, int errno);
int		exit_error(char *cmd, char *path, int errno);
int		export_unset_error(char *cmd, char *path, int errno);

/* heredoc_error.c */
void	max_heredoc_error(void);

void	*parsing_error_return_null(t_env_list *env, char *msg, int status);
int		parsing_error(t_env_list *env, char *msg, int status);
int		raise_cmd_error(t_block *block, int errno);
int		raise_file_error(char *filename, int errno);
#endif