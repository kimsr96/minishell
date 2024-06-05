/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:41:23 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/05 14:36:09 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../libft/libft.h"
# include "../minishell.h"
# include <stdio.h>

/* echo.c */
void	ft_echo(t_token *token);

/* cd.c */
void	ft_cd(char *path);

/* pwd.c */
void	ft_pwd(void);

#endif
