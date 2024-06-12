/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:32:28 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/12 17:33:38 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../../libft/libft.h"
# include "../../parser/parser.h"
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>

/* check_cmd */
void	check_cmd(t_parser *parser);

/* echo.c */
void	ft_echo(char *str, int flag, int fd);

/* cd.c */
void	ft_cd(char *path);

/* pwd.c */
void	ft_pwd(void);
#endif