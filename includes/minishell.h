/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:00:06 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/13 15:25:28 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "env.h"
# include "error.h"
# include "command.h"
# include "tokenizer.h"
# include "parser.h"
# include "ft_signal.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

void	get_next_command_line(t_block *block, t_token *token, char *str);

#endif
