/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:51:07 by seungryk          #+#    #+#             */
/*   Updated: 2024/06/15 16:24:10 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include <stdlib.h>
#include "../libft/libft.h"

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}t_env_list;

/* env.c */
t_env_list	*get_env(t_env_list *head, char **envp);

/* env_utils.c */
void		free_env(t_env_list	*env);
void		add_back_env(t_env_list **head, t_env_list *new);
t_env_list	*new_env_list(char *key, char *value);

/* find_env.c */
void		change_value(t_env_list *env, char *key, char *value);
t_env_list	*find_key_node(t_env_list *env, char *find_key);
#endif