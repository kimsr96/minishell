/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:02:20 by hyeonble          #+#    #+#             */
/*   Updated: 2024/07/06 15:37:51 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../command.h"

int	is_directory(char *filename);
int	raise_file_error(char *filename, char *error);
int	check_file(t_redirect *redirection);
int	redirect(t_block **head, t_block *block);

#endif