/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 12:11:06 by sejpark           #+#    #+#             */
/*   Updated: 2020/08/05 17:44:53 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s)
	{
		while (s[len])
			len++;
	}
	return (len);
}

char	*ft_strdup(const char *s1)
{
	size_t	strlen;
	char	*result;
	size_t	i;

	strlen = ft_strlen(s1);
	result = (char*)malloc((strlen + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (i < strlen)
		{
			result[i] = s1[i];
			i++;
		}
		result[i] = '\0';
		return (result);
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*result;
	size_t	i;

	result = NULL;
	if (s1 && s2)
	{
		total_len = ft_strlen(s1) + ft_strlen(s2);
		result = (char*)malloc((total_len + 1) * sizeof(char));
		if (result)
		{
			i = 0;
			while (*s1)
				result[i++] = *s1++;
			while (*s2)
				result[i++] = *s2++;
			result[i] = '\0';
			return (result);
		}
	}
	return (result);
}
