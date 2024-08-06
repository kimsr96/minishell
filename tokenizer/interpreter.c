/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:12:22 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/05 21:26:38 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

//static int	get_env_string(t_token *token, char *s, t_env_list *env)
//{
//	int			i;
//	char		*find_key;
//	t_env_list	*target;

//	i = 0;
//	find_key = get_env_var_name(&s[i + 1], get_env_len(&s[i + 1]));
//	target = find_key_node(env, find_key);
//	free(find_key);
//	if (!target)
//		return (-1);
//	if (ft_strncmp(target->key, "?", 2) == 0)
//		token->data = ft_strjoin(target->value, &s[i + 2]);
//	return (ft_strdup(target->value));
//}

//static void	remove_quote(t_token *token, size_t len, int quote)
//{
//	int		i;
//	int		idx;
//	int		type;
//	char	*ret;

//	i = 0;
//	idx = 0;
//	if (ft_strlen(token->data) == len)
//		return ;
//	ret = malloc(sizeof(char) * (len + 1));
//	if (!ret)
//		exit(1);
//	ret[len] = '\0';
//	while (token->data[i])
//	{
//		type = get_quote_type(token, token->data[i]);
//		if (type == quote || type == 3)
//			ret[idx++] = token->data[i];
//		i++;
//	}
//	free(token->data);
//	token->data = ret;
//}

//static ssize_t	quote_len(t_token *token, int quote)
//{
//	int		type;
//	size_t	i;
//	size_t	len;

//	i = 0;
//	len = 0;
//	while (token->data[i])
//	{
//		type = get_quote_type(token, token->data[i]);
//		if (type == quote || type == 3)
//			len++;
//		i++;
//	}
//	if (token->quote_type)
//	{
//		perror("quote error");
//		return (-1);
//	}
//	return (len);
//}

static size_t	quote_len(t_token *token)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (token->data[i])
	{
		if (get_quote_type(token, token->data[i]))
			len++;
		i++;
	}
	if (token->quote_type)
	{
		perror("quote error");
		return (-1);
	}
	return (len);
}

static void	remove_quote(t_token *token, int len)
{
	int		i;
	int		idx;
	char	*ret;

	i = 0;
	idx = 0;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		exit(1);
	ret[len] = '\0';
	while (token->data[i])
	{
		if (get_quote_type(token, token->data[i]))
			ret[idx++] = token->data[i];
		i++;
	}
	free(token->data);
	token->data = ret;
}

static int	interprete_str_len(t_token *token, char *s, t_env_list *env)
{
	int			i;
	int			len;
	int			type;
	int			env_len;
	char		*find_key;
	t_env_list	*target;

	i = 0;
	len = 0;
	while (s[i])
	{
		type = get_quote_type(token, s[i]);
		if (s[i] == '$' && type != S_QUOTE)
		{
			env_len = get_env_len(&s[i + 1]);
			find_key = get_env_var_name(&s[i + 1], env_len);
			target = find_key_node(env, find_key);
			free(find_key);
			if (target)
				len += ft_strlen(target->value);
			i += env_len + 1;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

int	interpreter(t_token *token, char *s, t_env_list *env, int len)
{
	int			i;
	int			j;
	int			type;
	int			env_len;
	char		*find_key;
	t_env_list	*target;
	char		*ret;

	i = 0;
	j = 0;
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		perror("malloc error");
	while (s[i])
	{
		type = get_quote_type(token, s[i]);
		if (s[i] == '$' && type != S_QUOTE)
		{
			env_len = get_env_len(&s[i + 1]);
			find_key = get_env_var_name(&s[i + 1], env_len);
			target = find_key_node(env, find_key);
			free(find_key);
			if (target)
			{
				ft_strlcat(&ret[j], target->value, len + 1);
				j += ft_strlen(target->value);
			}
			else
			{
				token->data = NULL;
			}
			i += env_len + 1;
		}
		else
		{
			ret[j++] = s[i];
			i++;
		}
	}
	free(token->data);
	token->data = ret;
	return (0);
}

int	token_interpreter(t_token **head, t_env_list *env)
{
	int		len;
	int		q_len;
	t_token	*curr;

	curr = *head;
	while (curr)
	{
		curr->quote_type = DEFAULT;
		len = interprete_str_len(curr, curr->data, env);
		interpreter(curr, curr->data, env, len);
		q_len = quote_len(curr);
		if (q_len == -1)
			break ;
		remove_quote(curr, q_len);
		curr = curr->next;
	}
	//if (del_token(head))
	//	return (1);
	return (0);

}	