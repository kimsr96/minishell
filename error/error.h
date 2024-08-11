/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:08:35 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/11 17:29:56 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include "../parser/parser.h"
# include "../env/env.h"

typedef struct s_block t_block;

# define NOT_SET "not set"
# define NO_FILE_DIR "No such file or directory"
# define ERR_QUOTE "quote error"
# define ERR_PIPE "pipe error"

# define COMMAND_NOT_FOUND 1
# define NO_SUCH_FILE_OR_DIR 2
# define IS_A_DIRECTORY 3
# define PERMISSION_DENIED 4
# define ERR_SYNTAX "SyntaxError : invalid syntax"

int	    error_msg_with_status(char *cmd, char *path, char *msg, int status);
void    *parsing_error_return_null(t_env_list *env, char *msg, int status);
int	    parsing_error(t_env_list *env, char *msg, int status);
int	raise_cmd_error(t_block *block, int errno);
#endif