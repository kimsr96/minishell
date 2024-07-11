/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:32:28 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/10 18:21:00 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../../libft/libft.h"
# include "../../parser/parser.h"
# include "../../env/env.h"
# include "../command.h"
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>

/* ft_check_cmd */
int		is_builtin(t_block *block);
void	exec_builtin(t_block *block, t_env_list *env);

/* ft_cd.c */
void	ft_cd(t_block *block, t_env_list *env);

/* ft_echo.c */
void	ft_echo(char **str, int fd);

/* ft_env.c */
void	ft_env(t_env_list *env, int fd);

/* ft_exit.c */
void	ft_exit(void);

/* ft_exit_status.c */
void	ft_exit_status(void);

/* ft_export.c */
void	ft_export(t_env_list *head, char **str);

/* ft_export_no_option.c */
size_t	get_min_len(char *s1, char *s2);
void	sort_env(t_env_list *head);
void	sort_print_env(t_env_list *head);

/* ft_unset.c */
void	ft_unset(t_env_list *head, char **str);

/* pwd.c */
char	*ft_pwd(int flag);
#endif