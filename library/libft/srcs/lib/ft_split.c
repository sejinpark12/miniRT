/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:33:09 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 18:28:20 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		ft_split_cnt(char const *s, const char c)
{
	int cnt;
	int begin;

	cnt = 0;
	begin = 0;
	while (*s)
	{
		if (begin == 0)
		{
			if (*s != c)
				begin = 1;
		}
		else
		{
			if (*s == c)
			{
				begin = 0;
				cnt++;
			}
		}
		s++;
	}
	return (begin == 0 ? cnt : cnt + 1);
}

int		ft_word_len(char const *s, const char c)
{
	int len;
	int begin;

	len = 0;
	begin = 0;
	while (*s)
	{
		if (begin == 0)
		{
			if (*s != c)
			{
				begin = 1;
				len++;
			}
		}
		else
		{
			if (*s == c)
				break ;
			else
				len++;
		}
		s++;
	}
	return (len);
}

char	*ft_alloc_word(int *idx, char const *s, const char c)
{
	int		word_len;
	char	*word;
	int		i;

	word_len = ft_word_len(&s[*idx], c);
	word = (char*)malloc(sizeof(char) + (word_len + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		word[i] = s[*idx + i];
		i++;
	}
	word[i] = '\0';
	*idx += word_len;
	return (word);
}

void	*ft_free(char **result, int len)
{
	int i;

	i = 0;
	while (i < len)
		free(result[i++]);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		cursor;
	char	**result;

	if (s == NULL)
		return (NULL);
	i = 0;
	cursor = 0;
	result = (char**)malloc(sizeof(char*) * (ft_split_cnt(s, c) + 1));
	if (result == NULL)
		return (NULL);
	while (s[cursor])
	{
		if (s[cursor] == c)
			cursor++;
		else
		{
			result[i] = ft_alloc_word(&cursor, s, c);
			if (result[i] == NULL)
				return (ft_free(result, i));
			i++;
		}
	}
	result[i] = 0;
	return (result);
}
