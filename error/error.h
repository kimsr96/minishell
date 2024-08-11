/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:08:35 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/11 17:06:46 by hyeonble         ###   ########.fr       */
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

int	error_msg_with_status(char *cmd, char *path, char *msg, int status);
int	parsing_error(t_env_list *env, char *msg, int status);
int	raise_cmd_error(t_block *block, int errno);
#endif