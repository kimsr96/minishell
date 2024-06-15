/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:32:28 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/15 16:44:02 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../../libft/libft.h"
# include "../../parser/parser.h"
# include "../../env/env.h"
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>

/* check_cmd */
int		check_cmd(t_parser *parser, t_env_list *env);

/* cd.c */
void	ft_cd(t_parser *parser, t_env_list *env);

/* echo.c */
void	ft_echo(char **str, int fd);

/* env.c */
void	ft_env(t_env_list *env, int fd);

/* exit.c */
void    ft_exit(void);

/* pwd.c */
char    *ft_pwd(int flag);
#endif