/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:02:20 by hyeonble          #+#    #+#             */
/*   Updated: 2024/08/13 16:36:38 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "command.h"
# include <fcntl.h>
# include <unistd.h>

int	is_directory(char *filename);
int	check_file(t_redirect *redirection);
int	redirect(t_redirect *redir);

#endif