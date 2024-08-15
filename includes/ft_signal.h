/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 10:24:14 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/14 23:23:17 by hyeonble         ###   ########.fr       */
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

extern int	g_sigint;
# define OFF 0
# define ON 1
/* ft_signal.h */
void	set_signal(void);
void	handle_sigint(int signal);
// void	handle_sigint_exec(int signal);
// void	handle_sigint_heredoc(int signal);
void 	set_signal(void);
void	set_terminal_print(int	mode);
#endif