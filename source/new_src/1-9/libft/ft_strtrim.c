/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 13:12:21 by sejpark           #+#    #+#             */
/*   Updated: 2020/07/15 14:49:33 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_trimfind(const char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_delete_trim(char const *s1, char const *set, size_t *cur)
{
	size_t idx;
	size_t str_len;
	size_t last_idx;
	size_t trimmed_len;

	idx = 0;
	str_len = ft_strlen(s1);
	last_idx = str_len - 1;
	trimmed_len = 0;
	while (ft_trimfind(s1[idx], set))
		idx++;
	if (idx > last_idx)
		trimmed_len = 0;
	else
	{
		*cur = idx;
		while (ft_trimfind(s1[last_idx], set))
		{
			last_idx--;
			idx++;
		}
		trimmed_len = str_len - idx;
	}
	return (trimmed_len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	trimmed_len;
	size_t	i;
	size_t	cur;
	char	*result;

	i = 0;
	cur = 0;
	result = NULL;
	if (s1)
	{
		trimmed_len = ft_delete_trim(s1, set, &cur);
		result = (char*)malloc((trimmed_len + 1) * sizeof(char));
		if (result)
		{
			while (i < trimmed_len)
				result[i++] = s1[cur++];
			result[i] = 0;
		}
	}
	return (result);
}
