/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:44:48 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 18:28:20 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	i;
	unsigned int	str_len;

	result = NULL;
	if (s)
	{
		str_len = ft_strlen(s);
		if (str_len <= start)
			len = 0;
		else if (str_len - start < len)
			len = str_len - start;
		result = (char*)malloc((len + 1) * sizeof(char));
		if (result)
		{
			i = 0;
			while (s[start + i] && i < len)
			{
				result[i] = s[start + i];
				i++;
			}
			result[i] = '\0';
		}
	}
	return (result);
}
