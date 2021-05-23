/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 14:15:26 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 18:28:20 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	find_str(const char *current, const char *needle)
{
	size_t i;

	i = 0;
	while (needle[i])
	{
		if (current[i] != needle[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char*)haystack);
	else if (len == 0)
		return (NULL);
	else
	{
		while (len - needle_len >= i)
		{
			if (haystack[i] == 0)
				break ;
			else if (find_str(&haystack[i], needle))
				return ((char*)&haystack[i]);
			else
				i++;
		}
		return (NULL);
	}
}
