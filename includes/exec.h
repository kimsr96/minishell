/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:02:20 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/13 14:26:34 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "command.h"
# include <fcntl.h>
# include <unistd.h>

int	is_directory(char *filename);
int	raise_file_error(char *filename, char *error);
int	check_file(t_redirect *redirection);
int	redirect(t_redirect *redir);

#endif