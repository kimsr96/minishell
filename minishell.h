/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:00:06 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/24 15:36:57 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./env/env.h"
# include "./command/command.h"
# include "./tokenizer/tokenizer.h"
# include "./parser/parser.h"
# include "./command/command.h"
# include "./signal/ft_signal.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

int status;

#endif
