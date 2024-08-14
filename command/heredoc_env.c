/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:46:30 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/14 15:49:24 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void    heredoc_env_expansion(char *line)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (line[i])
	{
		type = token->quote_type;
		if (is_expansion(token, env, &(token->data[i]), j))
		{			
			if (j != 0)
				token->space = 1;
			j += env_expansion(token, env, &token->data[i + 1], &ret[j]);
			i += get_env_len(&token->data[i + 1]);
		}
		else if (type == token->quote_type)
			ret[j++] = token->data[i];
	}
}