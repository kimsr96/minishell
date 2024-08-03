/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungryk <seungryk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 22:42:18 by seungryk          #+#    #+#             */
/*   Updated: 2024/08/03 11:56:12 by seungryk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	check_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_str(char *str, char *charset)
{
	int	i;
	int	len;
	int	cnt;

	i = -1;
	cnt = 0;
	while (str[++i])
		;
	len = i;
	if (len == 0)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (check_charset(str[i], charset))
		{
			if (i == 0 || i == len - 1)
				continue ;
			cnt += 1;
		}
	}
	return (cnt + 1);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*put_word(char *word, char *charset)
{
	int		i;
	int		last;
	char	*dest;

	i = -1;
	last = 0;
	while (!check_charset(word[last], charset) && word[last])
			last++;
	dest = (char *)malloc(sizeof(char) * (last + 1));
	if (!dest)
		return (0);
	ft_strncpy(dest, word, last);
	return (dest);
}

char	**ft_split2(char *str, char *charset)
{
	int		i;
	int		index;
	char	**arr;

	index = 0;
	if (!count_str(str, charset))
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (count_str(str, charset) + 1));
	if (!arr)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (!check_charset(str[i], charset))
		{
			arr[index] = put_word(&str[i], charset);
			index++;
			while (str[++i] && !check_charset(str[i], charset))
				;
		}
	}
	arr[index] = NULL;
	return (arr);
}
