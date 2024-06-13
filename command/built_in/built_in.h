/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:32:28 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/13 16:55:15 by seungryk         ###   ########.fr       */
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
int     check_cmd(t_parser *parser);

/* cd.c */
void	ft_cd(t_parser *parser);

/* echo.c */
void	ft_echo(char **str, int fd);

/* env.c */
void	ft_env(char **envp, int fd);

/* exit.c */
void    ft_exit(void);

/* pwd.c */
void	ft_pwd(void);
#endif