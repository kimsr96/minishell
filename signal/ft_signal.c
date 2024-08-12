/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 10:24:17 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/12 17:43:13 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"

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

void	handle_sigint_exec(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_putstr_fd("\n", 1);
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
