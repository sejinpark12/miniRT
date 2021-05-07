/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 14:31:51 by sejpark           #+#    #+#             */
/*   Updated: 2020/07/15 18:26:10 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	int		i;

	if (s == NULL)
		return (NULL);
	result = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (result)
	{
		i = 0;
		while (s[i])
		{
			result[i] = f((unsigned int)i, s[i]);
			i++;
		}
		result[i] = '\0';
	}
	return (result);
}
