/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 10:24:17 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/18 17:14:09 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		g_sigint = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		rl_redisplay();
	}
}

void	handle_sigint_exec(int signal)
{
	(void)signal;
	set_terminal_print(ON);
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_putstr_fd("\n", 1);
}

void	handle_sigint_heredoc(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(1);
}

void	set_signal(void)
{
	set_terminal_print(OFF);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	set_terminal_print(int mode)
{
	struct termios	term;

	if (mode == OFF)
	{
		tcgetattr(1, &term);
		term.c_lflag &= ~(ECHOCTL);
		tcsetattr(1, 0, &term);
		return ;
	}
	if (mode == ON)
	{
		tcgetattr(1, &term);
		term.c_lflag |= (ECHOCTL);
		tcsetattr(1, 0, &term);
		return ;
	}
}
