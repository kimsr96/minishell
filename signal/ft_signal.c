/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 10:24:17 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/10 13:15:26 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"

void	disable_raw_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_termios);
}

void	enable_raw_mode(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &g_termios);
    atexit(disable_raw_mode);
	raw = g_termios;
	tcgetattr(STDIN_FILENO, &g_termios);
	atexit(disable_raw_mode);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		rl_redisplay();
	}
}

void	set_signal(void)
{
	struct sigaction	act;

	if (sigemptyset(&act.sa_mask) == -1)
		exit(1);
	if (sigaddset(&act.sa_mask, SIGINT) == -1)
		exit(1);
	act.sa_handler = signal_handler;
	act.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &act, NULL) == -1)
		exit(1);
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		exit(1);
}
