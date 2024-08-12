/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 10:24:14 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/12 16:52:13 by seungryk         ###   ########.fr       */
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

/* ft_signal.h */
void	set_signal(void);
void	signal_handler(int signal);
#endif