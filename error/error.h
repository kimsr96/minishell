/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:08:35 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/04 12:05:20 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>

# define NOT_SET "not set"
# define NO_FILE_DIR "No such file or directory"

int	error_msg_with_status(char *cmd, char *path, char *msg, int status);
#endif