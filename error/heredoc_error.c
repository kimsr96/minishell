/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:59:52 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/15 17:13:55 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	max_heredoc_error(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("maximum here-document count exceeded\n", STDERR_FILENO);
}
