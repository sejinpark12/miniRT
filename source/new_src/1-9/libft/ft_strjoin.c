/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:58:11 by sejpark           #+#    #+#             */
/*   Updated: 2020/07/15 15:00:06 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
