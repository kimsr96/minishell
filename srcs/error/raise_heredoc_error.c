/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raise_heredoc_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:59:52 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/17 17:04:19 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	max_heredoc_error(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("maximum here-document count exceeded\n", STDERR_FILENO);
}
