/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:32:28 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/04 12:12:05 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../../libft/libft.h"
# include "../../parser/parser.h"
# include "../../env/env.h"
# include "../../error/error.h"
# include "../command.h"
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>

/* ft_check_cmd */
int		is_builtin(t_block *block);
void	exec_builtin(t_block *block, t_env_list *env);

/* ft_cd.c */
int		ft_cd(t_block *block, t_env_list *env);

/* ft_echo.c */
int		ft_echo(char **str, int fd);

/* ft_env.c */
int		ft_env(t_env_list *env, int fd);

/* ft_exit.c */
int		ft_exit(void);

/* ft_export.c */
int		ft_export(t_env_list *head, char **str);

/* ft_export_no_option.c */
size_t	get_min_len(char *s1, char *s2);
void	sort_env(t_env_list *head);
void	sort_print_env(t_env_list *head);

/* ft_unset.c */
int		ft_unset(t_env_list *head, char **str);

/* pwd.c */
int		ft_pwd(void);
#endif