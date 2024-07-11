/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonble <hyeonble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:51:07 by seungryk          #+#    #+#             */
/*   Updated: 2024/07/05 16:27:20 by hyeonble         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}t_env_list;

/* env.c */
int			get_key_len(char *envp);
char		*get_key(char *envp, int len);
char		*get_value(char *envp, int len);
t_env_list	*get_env(t_env_list *head, char **envp);

/* env_utils.c */
void		free_env(t_env_list	*env);
void		add_back_env(t_env_list **head, t_env_list *new);
t_env_list	*new_env_list(char *key, char *value);

/* find_env.c */
void		add_env_value(t_env_list *head, char *key, char *value);
void		change_env_value(t_env_list *head, char *key, char *value);
t_env_list	*find_key_node(t_env_list *env, char *find_key);

char		**get_envp(t_env_list *env);
#endif