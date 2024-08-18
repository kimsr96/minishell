/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 10:24:14 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/18 20:05:15 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <termios.h>
# include <readline/readline.h>
# include "libft.h"
# include "minishell.h"

# define OFF 0
# define ON 1

void	set_signal(void);
void	handle_sigint(int signal);
void	set_terminal_print(int mode);
#endif