/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 10:24:14 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/03 16:32:59 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <termios.h>
# include <readline/readline.h>
# include "../libft/libft.h"

struct termios  g_termios;

/* ft_signal.h */
void	set_signal(void);
void	enable_raw_mode(void);
void	disable_raw_mode(void);
void	signal_handler(int signal);
#endif